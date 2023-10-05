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
  TileStorage* TileStorage::get() { static TileStorage i; return &i; }
  String TileStorage::storagePath() const { return m_storagePath; }
  void TileStorage::setStoragePath(const String & path) { m_storagePath = path; }

  bool TileStorage::load(int8_t latitude, int16_t longitude)
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

  int16_t TileStorage::elevation(const double latitude, const double longitude) const
  {
    TileKey key(latitude, longitude);
    if(not m_storage.count(key) or m_storage.at(key) == nullptr)
      throw std::runtime_error(scope_information_str + "Access to non-created tile (1)");

    try
    {
      return m_storage.at(key).get()->elevation(latitude, longitude);
    }
    catch(std::runtime_error& x) { throw x; }
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

  TileKey::TileKey(int8_t latitude, int16_t longitude)
    : latitude(latitude)
    , longitude(longitude)
  {}

  TileKey::TileKey(double latitude, double longitude)
    : latitude(floor(latitude))
    , longitude(floor(longitude))
  {}
} // QtEx
