//
// Created by whs31 on 10.10.2023.
//

#pragma once

#include <QtCore/QObject>
#include <QtCore/QMetaType>
#include <QtCore/QVariant>
#include <QtExCore/Global>

namespace QtEx
{
  class ISettingsProvider : public Object
  {
    Q_OBJECT

    public:
      [[nodiscard]] invokable virtual QVariant read(const QString& key, const QString& fid = QString()) const noexcept = 0;
      virtual void write(const String& key, const Variant& value, const String& fid = String()) noexcept = 0;

      virtual void load() noexcept = 0;
      virtual void save() const noexcept = 0;

    protected:
      explicit ISettingsProvider(Object* parent = nullptr) noexcept;
  };
} // QtEx

Q_DECLARE_METATYPE(QtEx::ISettingsProvider*)
Q_DECLARE_INTERFACE(QtEx::ISettingsProvider, "ISettingsProvider")

namespace QtEx
{
  inline ISettingsProvider::ISettingsProvider(Object* parent) noexcept
    : Object(parent)
  {}
} // QtEx