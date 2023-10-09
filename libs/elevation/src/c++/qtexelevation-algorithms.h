//
// Created by whs31 on 29.09.23.
//

#pragma once

#include <vector>
#include <utility>
#include <cstdint>
#include <QtPositioning/QGeoCoordinate>
#include <QtExCore/Global>
#include <QtExGeo/Math>
#include "QtExElevation/Types"

using std::vector;
using std::pair;

class QGeoPath;
class QGeoPolygon;

namespace QtEx
{
  enum class PreLoad
  {
    True,
    False
  };

  auto loadTile(i8 latitude, i16 longitude) -> bool;
  auto loadTiles(i8 minLatitude, i16 minLongitude, i8 maxLatitude, i16 maxLongitude) -> bool;
  auto loadTiles(const QGeoPath& path) -> bool;

  auto elevation(f64 latitude, f64 longitude, PreLoad mode = PreLoad::False) -> i16;

  template<typename T = i16>
  T elevation(const GeoCoordinate& coordinate, PreLoad mode = PreLoad::False);

  auto buildProfile(const QGeoPath& path, u8 discrete = 10) -> vector<pair<u32, i16>>;
  auto buildProfileAsGeoPath(const QGeoPath& path, f32 step = 1.f) -> QGeoPath;
} // QtEx

namespace QtEx
{
  template<typename T>
  T elevation(const GeoCoordinate& coordinate, PreLoad mode) { return static_cast<T>(elevation(coordinate.latitude(), coordinate.longitude(), mode)); }
} // QtEx
