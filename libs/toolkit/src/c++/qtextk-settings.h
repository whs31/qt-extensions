//
// Created by whs31 on 10.10.2023.
//

#pragma once

#include <QtCore/QObject>
#include <QtCore/QVariant>
#include <QtQml/qqml.h>
#include <QtExCore/Global>
#include <QtExToolkit/ISettingsProvider>

namespace QtEx
{
  class Settings : public Object
  {
    Q_OBJECT

    public:
      Settings(const Settings&) = delete;
      Settings(Settings&&) = delete;
      Settings& operator=(const Settings&) = delete;
      Settings& operator=(Settings&&) = delete;

      static auto get(ISettingsProvider* provider = nullptr) -> Settings*;

      [[nodiscard]] ISettingsProvider* io() const;      void setIo(ISettingsProvider*);

      invokable void write(const QString& key, const QVariant& value, const QString& json_path = QString()) const noexcept; // @todo
      invokable

    signals:
      void ioChanged();

    private:
      explicit Settings(ISettingsProvider* provider, Object* parent = nullptr);

    private:
      ISettingsProvider* m_io;
  };
} // QtEx

