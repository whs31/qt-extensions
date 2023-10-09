//
// Created by whs31 on 09.10.2023.
//

#pragma once

#include <QtCore/QObject>
#include <QtQml/qqml.h>
#include <QtExCore/Global>

namespace QtEx
{
  class QuickUtils : public Object
  {
    Q_OBJECT

    public:
      static auto get() -> QuickUtils*;
      static auto create(QQmlEngine* qml_engine, QJSEngine* js_engine) -> QuickUtils*;

      invokable QString uuid();

    private:
      explicit QuickUtils(Object* parent = nullptr);
  };
} // QtEx

