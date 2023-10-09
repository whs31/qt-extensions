//
// Created by whs31 on 09.10.2023.
//

#include "qtexsg-quickutils.h"
#include <QtCore/QUuid>

namespace QtEx
{
  auto QuickUtils::get() -> QuickUtils* { static QuickUtils instance; return &instance; }
  auto QuickUtils::create(QQmlEngine* qml_engine, QJSEngine* js_engine) -> QuickUtils* { return get(); }

  QuickUtils::QuickUtils(Object* parent)
    : Object(parent)
  {}

  auto QuickUtils::uuid() -> String { return QUuid::createUuid().toString(); }
} // QtEx