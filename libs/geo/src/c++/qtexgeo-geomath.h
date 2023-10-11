//
// Created by whs31 on 29.09.23.
//

#pragma once

#include <cstdint>

class QGeoCoordinate;
class QGeoPath;
class QPointF;

#if !defined(QTEX_CORE_MAKE_PUBLIC_ALIAS_FOR_QT_CLASSES)
namespace QtEx
{
#endif
using GeoCoordinate = QGeoCoordinate;
using GeoPath = QGeoPath;
#if !defined(QTEX_CORE_MAKE_PUBLIC_ALIAS_FOR_QT_CLASSES)
} // QtEx
#endif

namespace QtEx
{
  struct NEDPoint
  {
    NEDPoint();
    NEDPoint(float x, float y, float z);

    float x, y, z;
  };

  double mqiZoomLevel(double latitude, float ratio = 1) noexcept;
  QPointF geo2webmercator(const GeoCoordinate& geo, int zoom = 19) noexcept;
  NEDPoint geo2ned(const GeoCoordinate& coord, const GeoCoordinate& origin) noexcept;
  GeoCoordinate ned2geo(const NEDPoint& ned, const GeoCoordinate& origin) noexcept;
} // QtEx
