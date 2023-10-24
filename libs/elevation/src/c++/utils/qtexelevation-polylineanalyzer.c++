//
// Created by whs31 on 11.10.2023.
//

#include "qtexelevation-polylineanalyzer.h"
#include <stdexcept>
#include <QtCore/QPointF>
#include <QtCore/QLineF>
#include <QtConcurrent/QtConcurrentRun>
#include <QtExCore/Math>
#include <QtExElevation/Algorithms>

using std::runtime_error;

namespace QtEx
{
  auto PathAnalyzer::checkTileStatus(const GeoPath& path) -> TileStatus
  {
    if(path.isEmpty())
      return InvalidPath;

    auto tileExists = [](const GeoCoordinate& coord) -> bool {
        return elevation(coord, PreLoad::True).has_value();
    };
    bool was_present = tileExists(path.path().front());

    for (int i = 1; i < path.size(); ++i) {
      auto pointCheck = tileExists(path.coordinateAt(i));
      if((not was_present and pointCheck) or (was_present and not pointCheck)) {
          return PartiallyMissing;
      }
      was_present = pointCheck;
    }
    if(not was_present)
      return FullyMissing;
    return Present;
  }

  auto PathAnalyzer::checkForIntersection(const GeoPath& path) -> expected<bool, ErrorCode>
  {
    if(checkTileStatus(path) != Present)
      return unexpected(TilesUnavailable);
    if(path.isEmpty())
      return unexpected(EmptyPath);

    QGeoPath profile = buildProfileAsGeoPath(path, PRECISION);
    vector<IntersectionPoint> path_profile = PathAnalyzer::fillProfile(path.path(), path);
    vector<IntersectionPoint> ground_profile = PathAnalyzer::fillProfile(profile.path(), profile);
    vector<IntersectionPoint> result_path;
    for(auto point : path_profile)
    {
      if(not result_path.empty())
      {
        if(ground_profile.size() > 1)
        {
          for(isize i = 1; i < ground_profile.size(); i++)
          {
            QPointF f;
            QLineF a(result_path.back().distance, result_path.back().altitude, point.distance, point.altitude);
            QLineF b(ground_profile[i-1].distance, ground_profile[i-1].altitude, ground_profile[i].distance, ground_profile[i].altitude);
            if(a.intersects(b, &f) == QLineF::BoundedIntersection)
              result_path.emplace_back(static_cast<f32>(f.y()),
                                       static_cast<f32>(f.x()),
                                       false,
                                       (result_path.back().state == IntersectionPoint::InsideGround
                                        or result_path.back().state == IntersectionPoint::IntersectingIn)
                                       ? IntersectionPoint::IntersectingIn : IntersectionPoint::IntersectingOut,
                                       result_path.back().coordinate.atDistanceAndAzimuth(f.x() - result_path.back().distance,
                                       result_path.back().coordinate.azimuthTo(result_path.back().coordinate))
              );
          }
        }
      }

      point.state = (point.altitude > elevation(point.coordinate).value())
          ? IntersectionPoint::NonIntersecting : IntersectionPoint::InsideGround;
      result_path.push_back(point);
    }

    for(const auto& point : result_path)
      if(not point.base or point.state== IntersectionPoint::InsideGround)
        return true;
    return false;
  }

  auto PathAnalyzer::checkForIntersectionInBetween(const GeoCoordinate& a,
                                                   const GeoCoordinate& b) -> expected<bool, ErrorCode>
  {
    if(not a.isValid() or not b.isValid())
      return unexpected(InvalidArguments);
    GeoCoordinate p = a;
    p.setAltitude(elevation(p).value());
    f64 azimuth = a.azimuthTo(b);
    f64 distance = a.distanceTo(b);
    QLineF line(0, a.altitude(), distance, b.altitude());
    QPointF profile_segment_point(0, p.altitude());
    f64 d = PRECISION;
    while(d < distance)
    {
      GeoCoordinate dp = a.atDistanceAndAzimuth(d, azimuth);
      dp.setAltitude(elevation(dp).value());
      if(p.altitude() != dp.altitude())
      {
        QPointF profile_segment_point_2;
        if(p.altitude() > dp.altitude())
          profile_segment_point_2 = QPointF(d - PRECISION, p.altitude());
        else
          profile_segment_point_2 = QPointF(d, dp.altitude());
        QPointF dummy;
        if(line.intersects(QLineF(profile_segment_point, profile_segment_point_2), &dummy) == QLineF::BoundedIntersection)
          return true;
        profile_segment_point = profile_segment_point_2;
      }
      p = dp;
      d += PRECISION;
    }
    return false;
  }

  auto PathAnalyzer::checkForSlopeCompliance(const GeoPath& path, const vector<f32>& velocities, f32 roc, f32 rod,
                                             f32 hv) -> expected<bool, ErrorCode>
  {
    QGeoPath cp;
    if(path.isEmpty())
      return unexpected(EmptyPath);
    if(path.path().size() != velocities.size() and not velocities.empty())
      return unexpected(DynamicArraySizeMismatch);
    if(is_null(roc) or is_null(rod))
      return unexpected(InvalidArguments);
    cp.addCoordinate(path.path().first());
    for(isize i = 1; i < path.path().size(); i++)
    {
      const bool fallback = velocities[i] == 0;
      const auto dx = static_cast<f32>(path.path()[i].distanceTo(path.path()[i - 1]));
      const auto dy = static_cast<f32>(path.path()[i].altitude() - cp.path()[i - 1].altitude());
      const f32 dy_min = fallback ? rod * dx / hv : rod * dx / velocities[i];
      const f32 dy_max = fallback ? roc * dx / hv : roc * dx / velocities[i];
      auto result = path.path()[i];
      if((dy >= 0 and dy < dy_max) or (dy <= 0 and abs(dy) < dy_min))
      {
        cp.addCoordinate(result);
        continue;
      }
      else if((dy > 0 and dy > dy_max) or (dy < 0 and abs(dy) > dy_min))
        return false;
      cp.addCoordinate(result);
    }
    return true;
  }

  auto PathAnalyzer::fillProfile(const QList<GeoCoordinate>& list, const GeoPath& path) -> vector<IntersectionPoint>
  {
    vector<IntersectionPoint> ret;
    float distance = 0;
    for(int i = 0; i < list.size(); i++)
    {
      if(i)
        distance += static_cast<f32>(path.length(i - 1, i));
      const QGeoCoordinate& point = list[i];
      ret.emplace_back(static_cast<f32>(point.altitude()),
                       distance,
                       true,
                       IntersectionPoint::NonIntersecting,
                       QGeoCoordinate(point.latitude(), point.longitude())
      );
    }
    return ret;
  }

  PathAnalyzerAsync::PathAnalyzerAsync(Qt::Object* parent) noexcept
    : Qt::Object(parent)
  {
    qRegisterMetaType<expected<bool, QtEx::PathAnalyzer::ErrorCode>>("expected<bool, QtEx::PathAnalyzer::ErrorCode>");
  }

  void PathAnalyzerAsync::checkTileStatus(const GeoPath& path)
  {
    QtConcurrent::run([=](){
      emit tileStatusFinished(PathAnalyzer::checkTileStatus(path));
    });
  }

  void PathAnalyzerAsync::checkForIntersection(const GeoPath& path)
  {
    QtConcurrent::run([=](){
      emit intersectionFinished(PathAnalyzer::checkForIntersection(path));
    });
  }

  void PathAnalyzerAsync::checkForSlopeCompliance(const GeoPath& path, const vector<f32>& velocities, f32 roc, f32 rod, f32 hv)
  {
    QtConcurrent::run([=](){
      emit slopeComplianceFinished(PathAnalyzer::checkForSlopeCompliance(path, velocities, roc, rod, hv));
    });
  }
} // QtEx
