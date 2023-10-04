//
// Created by whs31 on 29.09.23.
//

#include "qtexgeo-googlemapsprovider.h"
#include <QtCore/QCoreApplication>
#include <QtCore/QDir>
#include <QtCore/QFile>

namespace QtEx
{
  GoogleMapsProvider::GoogleMapsProvider(Object* parent)
    : Object(parent)
    , m_path(QCoreApplication::applicationDirPath() + "/config/osm")
  {
    this->create();
  }

  String GoogleMapsProvider::path() const { return m_path; }
  void GoogleMapsProvider::setPath(const String& x) { m_path = x; /* ==> */ this->create(); }

  void GoogleMapsProvider::create() noexcept
  {
    QDir dir(path());
    if(not dir.exists())
      dir.mkpath(path());
    QFile::copy(":/osmconfigs/satellite", path() + "/satellite");
    QFile::copy(":/osmconfigs/terrain", path() + "/terrain");
    QFile::copy(":/osmconfigs/transit", path() + "/transit");
    QFile::copy(":/osmconfigs/cycle", path() + "/cycle");
    QFile::copy(":/osmconfigs/hiking", path() + "/hiking");
    QFile::copy(":/osmconfigs/night-transit", path() + "/night-transit");
    QFile::copy(":/osmconfigs/street", path() + "/street");
  }
} // QtEx