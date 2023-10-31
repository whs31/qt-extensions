//
// Created by whs31 on 29.10.2023.
//

#include "staticconfig.h"
#include <QtCore/QCoreApplication>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>

using Qt::Directory;
using Qt::File;
using Qt::String;

namespace QtEx
{
  StaticConfig::StaticConfig()
    : m_path(QCoreApplication::applicationDirPath() + "/cfg.json")
    , m_fallback(Qt::String())
  {}

  StaticConfig::StaticConfig(String path, String fallback)
    : m_path(path)
    , m_fallback(fallback)
  {
    (void)this->create();
  }

  String StaticConfig::path() const { return m_path; }
  void StaticConfig::setPath(const String& x) { m_path = x; }
  String StaticConfig::fallback() const { return m_fallback; }
  void StaticConfig::setFallback(const String& x) { m_fallback = x; }

  auto StaticConfig::create() -> bool
  {
    llog(Debug) "Looking for" << path();
    auto dir_path = path().remove(QUrl(path()).fileName());
    Directory directory(dir_path);
    if(not directory.exists())
    {
      directory.mkpath(dir_path);
      llog(Debug) "Created directory" << dir_path;
    }
    File file(path());
    if(not file.exists())
    {
      File::copy(fallback(), path());
      llog(Debug) "Placed fallback file into folder";
    }
    file.setPermissions(QFileDevice::ReadUser | QFileDevice::WriteUser);
    if(not file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
      llog(Error) "Failed to open file for read" << path();
      return false;
    }
    auto doc = QJsonDocument::fromJson(file.readAll());
    file.close();
    if(doc.isNull() or not doc.isObject())
    {
      llog(Error) "Invalid JSON";
      return false;
    }
    auto json = doc.object();
    for(auto it = json.begin(); it != json.end(); ++it)
      m_values.insert({
        it.key(),
        it.value().toVariant()
      });
    return true;
  }

  void StaticConfig::set(const String& key, const Qt::Variant& value) noexcept
  {
    m_locker.lock();
    m_values[key] = value;
    m_locker.unlock();
  }

  auto StaticConfig::value(const String& key) const noexcept -> expected<Qt::Variant, ConfigError>
  {
    m_locker.lock();
    if(not m_values.count(key))
      return unexpected(ConfigError::InvalidKey);
    auto ret = m_values.at(key);
    m_locker.unlock();
    return ret;
  }
} // QtEx