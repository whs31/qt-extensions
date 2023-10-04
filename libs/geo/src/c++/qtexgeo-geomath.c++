//
// Created by whs31 on 29.09.23.
//

#include "qtexgeo-geomath.h"
#include <QtCore/QPointF>
#include <QtPositioning/QGeoCoordinate>
#include <QtExCore/Math>
#include <QtExCore/Logging>

constexpr const double MAP_SCALE_RATIO = 156'543.03392;
constexpr const float EARTH_RADIUS = 6371000.f;

namespace QtEx
{
  NEDPoint::NEDPoint()
    : x(0)
    , y(0)
    , z(0)
  {}

  NEDPoint::NEDPoint(float x, float y, float z)
    : x(x)
    , y(y)
    , z(z)
  {}

  double mqiZoomLevel(double latitude, float ratio) noexcept {
    return log<double>(2, MAP_SCALE_RATIO * cos(deg2rad(latitude) / (compare<double>(ratio, 0) ? 1 : ratio)));
  }

  QPointF geo2webmercator(const GeoCoordinate& geo, int zoom) noexcept {
    return {(1.0 - std::asinh(tg(deg2rad(geo.latitude()))) / pi<float>) / 2.0 * (1 << zoom), (geo.longitude() + 180.0) / 360.0 * (1 << zoom)};
  }

  NEDPoint geo2ned(const GeoCoordinate& coord, const GeoCoordinate& origin) noexcept
  {
    if(coord == origin)
      return {};

    double sin_lat = sin(deg2rad(coord.latitude()));
    double cos_lat = cos(deg2rad(coord.latitude()));
    double cos_d_lon = cos(deg2rad(coord.longitude()) - deg2rad(origin.longitude()));
    double ref_sin_lat = sin(deg2rad(origin.latitude()));
    double ref_cos_lat = cos(deg2rad(origin.latitude()));

    double c = acos(ref_sin_lat * sin_lat + ref_cos_lat * cos_lat * cos_d_lon);
    double k = (abs(c) < std::numeric_limits<double>::epsilon()) ? 1.0 : (c / sin(c));

    return { static_cast<float>(k * (ref_cos_lat * sin_lat - ref_sin_lat * cos_lat * cos_d_lon) * EARTH_RADIUS),
        static_cast<float>(k * cos_lat * sin(deg2rad(coord.longitude()) - deg2rad(origin.longitude())) * EARTH_RADIUS),
        static_cast<float>(-(coord.altitude() - origin.altitude())) };
  }

  GeoCoordinate ned2geo(const NEDPoint& ned, const GeoCoordinate& origin) noexcept
  {
    double c = hypotenuse(ned.x / EARTH_RADIUS, ned.y / EARTH_RADIUS);
    double ref_sin_lat = sin(deg2rad(origin.latitude()));
    double ref_cos_lat = cos(deg2rad(origin.latitude()));
    double lat_rad, lon_rad;

    if(abs(c) > std::numeric_limits<double>::epsilon())
    {
      lat_rad = asin(cos(c) * ref_sin_lat + (ned.x / EARTH_RADIUS * sin(c) * ref_cos_lat) / c);
      lon_rad = (deg2rad(origin.longitude()) + std::atan2(ned.y / EARTH_RADIUS * sin(c),
                 c * ref_cos_lat * cos(c) - ned.x / EARTH_RADIUS * ref_sin_lat * sin(c)));
    }
    else
    {
      lat_rad = deg2rad(origin.latitude());
      lon_rad = deg2rad(origin.longitude());
    }
    return { rad2deg(lat_rad), rad2deg(lon_rad), -ned.z + origin.altitude() };
  }
} // QtEx