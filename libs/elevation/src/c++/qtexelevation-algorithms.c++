//
// Created by whs31 on 29.09.23.
//

#include "qtexelevation-algorithms.h"
#include <QtCore/QPointF>
#include <QtPositioning/QGeoPath>
#include <QtExCore/Math>
#include <QtExCore/Logging>
#include "QtExElevation/TileStorage"

namespace QtEx
{
  auto loadTile(const i8 latitude, const i16 longitude) -> bool { return TileStorage::get()->load(latitude, longitude); }
  auto loadTiles(const i8 minLatitude, const i16 minLongitude, const i8 maxLatitude, const i16 maxLongitude) -> bool
  {
    bool ret = true;
    for(i8 lat = minLatitude; lat <= maxLatitude; ++lat)
      for(i16 lon = minLongitude; lon <= maxLongitude; ++lon)
        ret &= loadTile(lat, lon);
    return ret;
  }

  auto elevation(const f64 latitude, const f64 longitude, PreLoad mode) -> expected<f32, ElevationError>
  {
    f64 lat = latitude;
    f64 lon = longitude;
    if (latitude - std::floor(latitude) < 0.00001)
      lat = std::floor(latitude);
    if(std::ceil(latitude) - latitude < 0.00001)
      lat = std::ceil(latitude);
    if(longitude - std::floor(longitude) < 0.00001)
      lon = std::floor(longitude);
    if(std::ceil(longitude) - longitude < 0.00001)
      lon = std::ceil(longitude);

    if(mode == PreLoad::True)
      loadTile(static_cast<i8>(lat), static_cast<i16>(lon));

    return TileStorage::get()->elevation(lat, lon);
  }

  auto elevation(const GeoCoordinate& coord, PreLoad mode) -> expected<f32, ElevationError>
  {
    return elevation(coord.latitude(), coord.longitude(), mode);
  }

  auto buildProfile(const QGeoPath& path, u8 discrete) -> vector<pair<u32, i16>>
  {
    loadTiles(path);
    vector<pair<u32, i16>> groundProfile;
    if(path.size())
    {
      f64 distanceFromStart = 0;
      GeoCoordinate prevBasePointGeo = path.coordinateAt(0);
      for(GeoCoordinate point : path.path())
      {
        if(not groundProfile.empty())
        {
          f64 azimuth = prevBasePointGeo.azimuthTo(point);
          f64 distanceFromPrevBasePoint = prevBasePointGeo.distanceTo(point);

          f64 distance = discrete;
          GeoCoordinate prevDeltaPointGeo = prevBasePointGeo;
          while(distance < distanceFromPrevBasePoint)
          {
            GeoCoordinate deltaPointGeo = prevBasePointGeo.atDistanceAndAzimuth(distance, azimuth);
            auto a = deltaPointGeo.latitude();
            auto b = deltaPointGeo.longitude();
            auto c = prevDeltaPointGeo.latitude();
            auto d = prevDeltaPointGeo.longitude();
            auto e = point.latitude();
            auto f = point.longitude();

            auto new_altitude = elevation(deltaPointGeo);
            if(not new_altitude.has_value())
              return {};
            deltaPointGeo.setAltitude(new_altitude.value());
            if(prevDeltaPointGeo.altitude() != deltaPointGeo.altitude())
            {
              if(prevDeltaPointGeo.altitude() > deltaPointGeo.altitude())
                groundProfile.emplace_back(distance - discrete + distanceFromStart, prevDeltaPointGeo.altitude());
              else
                groundProfile.emplace_back(distance + distanceFromStart, deltaPointGeo.altitude());
            }
            prevDeltaPointGeo = deltaPointGeo;
            distance += discrete;
          }
          distanceFromStart += distanceFromPrevBasePoint;
        }
        auto new_altitude = elevation(point);
        if(not new_altitude.has_value())
          return {};
        point.setAltitude(new_altitude.value());
        groundProfile.emplace_back(distanceFromStart, point.altitude());
        prevBasePointGeo = point;
      }
    }
    return groundProfile;
  }

  auto loadTiles(const QGeoPath& path) -> bool
  {
    if(path.isEmpty())
      return false;
    if(path.size() == 1)
      return loadTile(std::floor(path.coordinateAt(0).latitude()), std::floor(path.coordinateAt(0).longitude()));

    i8 minLatitude = 0;
    i8 maxLatitude = 0;
    i16 minLongitude = 0;
    i16 maxLongitude = 0;

    bool ret = true;
    for(usize i = 1; i < path.size(); ++i)
    {
      GeoCoordinate coord1 = path.coordinateAt(i - 1);
      GeoCoordinate coord2 = path.coordinateAt(i);
      minLatitude = coord1.latitude() < coord2.latitude() ? static_cast<i8>(coord1.latitude()) : static_cast<i8>(coord2.latitude());
      maxLatitude = coord1.latitude() < coord2.latitude() ? static_cast<i8>(coord2.latitude()) : static_cast<i8>(coord1.latitude());
      minLongitude = coord1.longitude() < coord2.longitude() ? static_cast<i16>(coord1.longitude()) : static_cast<i16>(coord2.longitude());
      maxLongitude = coord1.longitude() < coord2.longitude() ? static_cast<i16>(coord2.longitude()) : static_cast<i16>(coord1.longitude());
      ret &= loadTiles(minLatitude, minLongitude, maxLatitude, maxLongitude);
    }
    return ret;
  }

  auto buildProfileAsGeoPath(const QGeoPath& path, float step) -> QGeoPath
  {
    if(not loadTiles(path))
      return {};
    QGeoPath ret;
    for(auto point : path.path())
    {
      if(ret.size())
      {
        auto previous = ret.coordinateAt(ret.size() - 1);
        auto azimuth = previous.azimuthTo(point);
        auto delta = previous.distanceTo(point);
        f32 delta2 = step;
        auto t = previous;
        while(delta2 < delta)
        {
          auto u = previous.atDistanceAndAzimuth(delta2, azimuth);
          auto alt = elevation(u);
          if(not alt.has_value())
            return ret;
          u.setAltitude(alt.value());
          if(t.altitude() != u.altitude())
          {
            if(t.altitude() > u.altitude()) ret.addCoordinate(t);
            else ret.addCoordinate(u);
          }
          t = u;
          delta2 += step;
        }
      }
      auto alt = elevation(point);
      if(not alt.has_value())
        return ret;
      point.setAltitude(alt.value());
      ret.addCoordinate(point);
    }
    return ret;
  }
} // QtEx
