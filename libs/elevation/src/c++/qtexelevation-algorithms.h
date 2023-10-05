//
// Created by whs31 on 29.09.23.
//

#pragma once

#include <vector>
#include <utility>
#include <cstdint>
#include "QtExElevation/Types"

using std::vector;
using std::pair;

class QGeoCoordinate;
class QGeoPath;
class QGeoPolygon;

namespace QtEx
{
  bool loadTile(int8_t latitude, int16_t longitude);
  bool loadTiles(int8_t minLatitude, int16_t minLongitude, int8_t maxLatitude, int16_t maxLongitude);
  bool loadTiles(const QGeoPath & _path);

  int16_t elevation(double latitude, double longitude);

  auto buildProfile(const QGeoPath& path, uint8_t discrete = 10) -> vector<pair<uint32_t, int16_t>>;
  QGeoPath buildProfileAsGeoPath(const QGeoPath& path, float step = 1.f);
} // QtEx
