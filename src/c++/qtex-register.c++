//
// Created by whs31 on 09.10.2023.
//

#include "qtex-register.h"
#include <QtQml/qqml.h>
#include <QtExtensionsGeo/TileLoader>
#include <QtExtensionsGeo/GoogleMapsProvider>
#include <QtExtensionsScenegraph/QuickUtils>

namespace QtEx
{
  void registerTypes(const char* uri, int major, int minor) noexcept
  {
    qmlRegisterModule(uri, major, minor);
    qmlRegisterSingletonType<QuickUtils>(uri, major, minor, "XUtils", QuickUtils::create);
    qmlRegisterType<GoogleMapsProvider>(uri, major, minor, "XOsmProvider");
  }
} // QtEx