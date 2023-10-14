//
// Created by whs31 on 29.09.23.
//

#include "qtexelevation-tilestorage.h"
#include <memory>
#include <QtCore/QCoreApplication>
#include <QtExCore/Logging>
#include <gdal.h>
#include "QtExElevation/Tile"

namespace QtEx
{
  auto TileStorage::get() -> TileStorage* { static TileStorage i; return &i; }

  String TileStorage::storagePath() const { return m_storagePath; }
  void TileStorage::setStoragePath(const String & path) { m_storagePath = path; }

  auto TileStorage::load(i8 latitude, i16 longitude) -> bool
  {
    TileKey key(latitude, longitude);
    if(not m_storage.count(key))
    {
      std::lock_guard<std::mutex> lock(m_mutex);
      if(not m_storage.count(key))
      {
        m_storage[key] = std::make_unique<Tile>(storagePath(), latitude, longitude);
      }
    }
    return m_storage.count(key);
  }

  auto TileStorage::elevation(const double latitude, const double longitude) const -> expected<f32, ElevationError>
  {
    TileKey key(latitude, longitude);
    if(not m_storage.count(key) or m_storage.at(key) == nullptr)
      return unexpected(ElevationError::TileNotFound);
    return m_storage.at(key).get()->elevation(latitude, longitude);
  }

  TileStorage::TileStorage()
    : m_storagePath(QCoreApplication::applicationDirPath() + "/elevations")
  {
    GDALAllRegister();
  }

  TileKey::TileKey()
    : latitude(0)
    , longitude(0)
  {}

  TileKey::TileKey(i8 latitude, i16 longitude)
    : latitude(latitude)
    , longitude(longitude)
  {}

  TileKey::TileKey(f64 latitude, f64 longitude)
    : latitude(floor(latitude))
    , longitude(floor(longitude))
  {}
} // QtEx
