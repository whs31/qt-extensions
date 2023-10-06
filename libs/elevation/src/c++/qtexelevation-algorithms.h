//
// Created by whs31 on 29.09.23.
//

#pragma once

#include <vector>
#include <utility>
#include <cstdint>
#include <QtPositioning/QGeoCoordinate>
#include <QtExGeo/Math>
#include "QtExElevation/Types"

using std::vector;
using std::pair;

class QGeoPath;
class QGeoPolygon;

namespace QtEx
{
  enum class PreLoad : uint8_t {
      True,
      False
  };

  bool loadTile(int8_t latitude, int16_t longitude);
  bool loadTiles(int8_t minLatitude, int16_t minLongitude, int8_t maxLatitude, int16_t maxLongitude);
  bool loadTiles(const QGeoPath & _path);

  int16_t elevation(double latitude, double longitude, PreLoad mode = PreLoad::False);
  template<typename T = int16_t> T elevation(const GeoCoordinate& coordinate, PreLoad mode = PreLoad::False);

  auto buildProfile(const QGeoPath& path, uint8_t discrete = 10) -> vector<pair<uint32_t, int16_t>>;
  QGeoPath buildProfileAsGeoPath(const QGeoPath& path, float step = 1.f);
} // QtEx

namespace QtEx
{
  template<typename T>
  T elevation(const GeoCoordinate& coordinate, PreLoad mode) { return static_cast<T>(elevation(coordinate.latitude(), coordinate.longitude(), mode)); }
} // QtEx
