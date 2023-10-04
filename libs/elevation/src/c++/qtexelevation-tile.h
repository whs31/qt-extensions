//
// Created by whs31 on 29.09.23.
//

#pragma once

#include <QtCore/QByteArray>
#include <QtExCore/Global>

namespace QtEx
{
  class Tile
  {
    public:
      Tile(const String& path, int8_t latitude, int16_t longitude);

      [[nodiscard]] int16_t elevation(double latitude, double longitude) const;

    private:
      double m_tllat, m_tllon;
      double m_latsize, m_lonsize;
      int m_tilexsize, m_tileysize;
      ByteArray m_tile;
  };
} // QtEx
