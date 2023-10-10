//
// Created by whs31 on 09.10.2023.
//

#include "qtexsg-quickutils.h"
#include <QtCore/QUuid>
#include <QtCore/QCoreApplication>

namespace QtEx
{
  auto QuickUtils::get() -> QuickUtils* { static QuickUtils instance; return &instance; }
  auto QuickUtils::create(QQmlEngine* qml_engine, QJSEngine* js_engine) -> QuickUtils* { return get(); }

  QuickUtils::QuickUtils(Object* parent)
    : Object(parent)
  {}

  auto QuickUtils::uuid() -> String { return QUuid::createUuid().toString(); }
  auto QuickUtils::qtVersionMajor() -> int { return QT_VERSION_MAJOR; }
  auto QuickUtils::qtVersionMinor() -> int { return QT_VERSION_MINOR; }
  auto QuickUtils::qtVersionPatch() -> int { return QT_VERSION_PATCH; }
  auto QuickUtils::qtVersion() -> String
  {
    return String("%1.%2.%3")
           .arg(qtVersionMajor())
           .arg(qtVersionMinor())
           .arg(qtVersionPatch());
  }

  auto QuickUtils::architecture() -> int
  {
    #if defined(Q_OS_WIN)
    return System::Windows;
    #elif defined(Q_OS_ANDROID)
    return System::Android;
    #elif defined(Q_OS_MACOS)
    return System::Mac;
    #elif defined(Q_OS_LINUX)
    return System::Linux;
    #else
    # error "Unknown architecture. Failed to compile QtEx library."
    #endif
  }

  auto QuickUtils::applicationDirectoryPath() -> String { return QCoreApplication::applicationDirPath(); }
  auto QuickUtils::blendColor(const Color& color, f32 alpha) -> Color
  {
    return { color.red(), color.green(), color.blue(), static_cast<i32>(alpha * 255) };
  }
} // QtEx