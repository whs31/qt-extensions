//
// Created by whs31 on 29.09.23.
//

#pragma once

#include <map>
#include <memory>
#include <mutex>
#include <QtCore/QString>
#include <QtExCore/Global>

using std::map;
using std::mutex;
using std::unique_ptr;

namespace QtEx
{
  class Tile;

  struct TileKey
  {
    TileKey();
    TileKey(int8_t latitude, int16_t longitude);
    TileKey(double latitude, double longitude);

    int8_t latitude;
    int16_t longitude;

    friend bool operator<(TileKey const& l, TileKey const& r)
    {
      if (l.latitude < r.latitude) return true;
      else if (l.latitude > r.latitude) return false;
      else return (l.longitude < r.longitude);
    }
  };

  class TileStorage
  {
    public:
      static TileStorage* get();
      TileStorage(TileStorage&) = delete;

      [[nodiscard]] String storagePath() const;  void setStoragePath(const String&);

      bool load(int8_t latitude, int16_t longitude);

      [[nodiscard]] int16_t elevation(double latitude, double longitude) const;

    private:
      TileStorage();

    private:
      String m_storagePath;
      map<TileKey, unique_ptr<Tile>> m_storage;
      mutex m_mutex;
  };

} // QtEx
