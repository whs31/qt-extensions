//
// Created by whs31 on 11.10.2023.
//

#pragma once

#include <vector>
#include <QtPositioning/QGeoPath>
#include <QtExCore/Global>
#include <QtExGeo/Math>
#include <QtExElevation/Types>
#include <Libra/Expected>

using std::vector;

namespace QtEx
{
  class PathAnalyzer
  {
    constexpr static f32 PRECISION = 1.f; // meters

    public:
      enum TileStatus
      {
        Present,
        PartiallyMissing,
        FullyMissing,
        InvalidPath
      };

      enum ErrorCode
      {
        TilesUnavailable,
        InvalidArguments,
        DynamicArraySizeMismatch,
        EmptyPath
      };

    public:
      static auto checkTileStatus(const GeoPath& path) -> TileStatus;
      static auto checkForIntersection(const GeoPath& path) -> expected<bool, ErrorCode>;
      static auto checkForIntersectionInBetween(const GeoCoordinate& a, const GeoCoordinate& b) -> expected<bool, ErrorCode>;
      static auto checkForSlopeCompliance(const GeoPath& path, const vector<f32>& velocities, f32 roc, f32 rod, f32 hv) -> expected<bool, ErrorCode>;

    private:
      static auto fillProfile(const QList<GeoCoordinate>& list, const GeoPath& path) -> vector<IntersectionPoint>;
  };
} // QtEx

Q_DECLARE_METATYPE(QtEx::PathAnalyzer::TileStatus)
Q_DECLARE_METATYPE(QtEx::PathAnalyzer::ErrorCode)

namespace QtEx
{
  class PathAnalyzerAsync : public Qt::Object
  {
    Q_OBJECT

    public:
      explicit PathAnalyzerAsync(Qt::Object* parent) noexcept;

      void checkTileStatus(const GeoPath& path);
      void checkForIntersection(const GeoPath& path);
      void checkForSlopeCompliance(const GeoPath& path, const vector<f32> &velocities, f32 roc, f32 rod, f32 hv);

    signals:
      void tileStatusFinished(QtEx::PathAnalyzer::TileStatus status);
      void intersectionFinished(expected<bool, QtEx::PathAnalyzer::ErrorCode> res);
      void slopeComplianceFinished(expected<bool, QtEx::PathAnalyzer::ErrorCode> res);
  };
} // QtEx
