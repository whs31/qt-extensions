//
// Created by whs31 on 29.10.2023.
//

#pragma once

#include <map>
#include <mutex>
#include <Libra/Expected>
#include <QtCore/QVariant>
#include <QtExtensions/Global>
#include <QtExtensions/Logging>

using std::map;
using std::mutex;

namespace QtEx
{
  class StaticConfig
  {
    public:
      enum class ConfigError
      {
        InvalidKey
      };

      enum class SetMode
      {
        WriteToFile,
        HoldInRAM
      };

      StaticConfig();
      StaticConfig(Qt::String path, Qt::String fallback);

      [[nodiscard]] Qt::String path() const;      void setPath(const Qt::String&);
      [[nodiscard]] Qt::String fallback() const;  void setFallback(const Qt::String&);

      auto create() -> bool;
      auto value(const Qt::String& key) const noexcept -> expected<Qt::Variant, ConfigError>;

      template<typename T>
      auto value(const Qt::String& key) const noexcept -> T;

      void set(const Qt::String& key, const Qt::Variant& value, SetMode) noexcept;
      void save() noexcept;

    private:
      mutable mutex m_locker;
      Qt::String m_path;
      Qt::String m_fallback;
      map<Qt::String, Qt::Variant> m_values;
  };
} // QtEx

namespace QtEx
{
  template<typename T>
  auto StaticConfig::value(const Qt::String& key) const noexcept -> T
  {
    auto val = this->value(key);
    if(not val.has_value())
    {
      llog(Error) "Failed to read key" << key;
      return Qt::Variant().value<T>();
    }
    return val.value().value<T>();
  }
} // QtEx

