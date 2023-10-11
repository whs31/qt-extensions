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

      [[nodiscard]] Variant read(const String& key, const String& fid = String()) const noexcept;

      template<typename T>
      [[nodiscard]] T read(const String& key, const String& fid = String()) const noexcept
      { return read(key, fid).value<T>(); }

      invokable void write(const QString& key, const QVariant& value, const QString& fid = QString()) const noexcept;
      invokable void save() noexcept;
      invokable void load() noexcept;
      invokable void revert() noexcept;

    signals:
      void ioChanged();
      void valueChanged(QString key, QString fid = QString());

    private:
      explicit Settings(ISettingsProvider* provider, Object* parent = nullptr);

    private:
      ISettingsProvider* m_io;
  };
} // QtEx

