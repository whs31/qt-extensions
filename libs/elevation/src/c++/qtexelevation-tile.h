//
// Created by whs31 on 29.09.23.
//

#pragma once

#include <QtCore/QByteArray>
#include <QtExCore/Global>
#include <Libra/Expected>
#include "qtexelevation-errorcodes.h"

using Qt::ByteArray;
using Qt::String;

namespace QtEx
{
  class Tile
  {
    public:
      Tile(const String& path, i8 latitude, i16 longitude);

      [[nodiscard]] auto elevation(double latitude, double longitude) const -> expected<f32, ElevationError>;

    private:
      f64 m_tllat;
      f64 m_tllon;
      f64 m_latsize;
      f64 m_lonsize;
      int m_tilexsize;
      int m_tileysize;
      ByteArray m_tile;
  };
} // QtEx
