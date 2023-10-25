//
// Created by whs31 on 29.09.23.
//

#include "qtexgeo-register.h"
#include <QtQml/qqml.h>
#include <QtExtensionsGeo/TileLoader>
#include <QtExtensionsGeo/GoogleMapsProvider>

namespace QtEx
{
  void Geo::registerQml() noexcept
  {
    qmlRegisterModule("QtEx.Geo", 1, 0);
    qmlRegisterType<GoogleMapsProvider>("QtEx.Geo", 1, 0, "QtExGoogleMapsProvider");
  }
} // QtEx