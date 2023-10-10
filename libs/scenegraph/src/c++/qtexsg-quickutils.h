//
// Created by whs31 on 09.10.2023.
//

#pragma once

#include <QtCore/QObject>
#include <QtGui/QColor>
#include <QtQml/qqml.h>
#include <QtExCore/Global>

namespace QtEx
{
  class QuickUtils : public Object
  {
    Q_OBJECT

    public:
      enum System
      {
        Windows,
        Linux,
        Mac,
        Android
      };
      Q_ENUM(System)

      QuickUtils(const QuickUtils&) = delete;
      QuickUtils(QuickUtils&&) = delete;
      QuickUtils& operator=(const QuickUtils&) = delete;
      QuickUtils& operator=(QuickUtils&&) = delete;

      static auto get() -> QuickUtils*;
      static auto create(QQmlEngine* qml_engine, QJSEngine* js_engine) -> QuickUtils*;

      invokable static QString uuid();
      invokable static int qtVersionMajor();
      invokable static int qtVersionMinor();
      invokable static int qtVersionPatch();
      invokable static QString qtVersion();
      invokable static int architecture();
      invokable static QString applicationDirectoryPath();
      invokable static QColor blendColor(const QColor& color, float alpha);

    private:
      explicit QuickUtils(Object* parent = nullptr);
  };
} // QtEx

