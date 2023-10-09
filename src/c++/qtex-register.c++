//
// Created by whs31 on 09.10.2023.
//

#include "qtex-register.h"
#include <QtQml/qqml.h>
#include <QtExScenegraph/QuickUtils>

namespace QtEx
{
  void registerTypes(const char* uri, int major, int minor) noexcept
  {
    qmlRegisterModule(uri, major, minor);
    qmlRegisterSingletonType<QuickUtils>(uri, major, minor, "QtExQuickUtils", QuickUtils::create);
  }
} // QtEx