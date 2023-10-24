//
// Created by whs31 on 29.09.23.
//

#pragma once

#include <map>
#include <memory>
#include <mutex>
#include <QtCore/QString>
#include <QtExCore/Global>
#include <Libra/Expected>
#include "qtexelevation-errorcodes.h"

using std::map;
using std::mutex;
using std::unique_ptr;
using Qt::String;

namespace QtEx
{
  class Tile;
  struct TileKey
  {
    TileKey();
    TileKey(i8 latitude, i16 longitude);
    TileKey(f64 latitude, f64 longitude);

    i8 latitude;
    i16 longitude;

    friend bool operator<(TileKey const& l, TileKey const& r)
    {
      if(l.latitude < r.latitude) return true;
      else if(l.latitude > r.latitude) return false;
      else return(l.longitude < r.longitude);
    }
  };

  class TileStorage
  {
    public:
      static auto get() -> TileStorage*;
      TileStorage(TileStorage&) = delete;

      [[nodiscard]] String storagePath() const;
      void setStoragePath(const String&);

      auto load(i8 latitude, i16 longitude) -> bool;

      [[nodiscard]] auto elevation(double latitude, double longitude) const -> expected<f32, ElevationError>;

    private:
      TileStorage();

    private:
      String m_storagePath;
      map<TileKey, unique_ptr<Tile>> m_storage;
      mutex m_mutex;
  };

} // QtEx
