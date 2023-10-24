//
// Created by whs31 on 11.10.2023.
//

#include "qtextk-monojsonsettingsprovider.h"
#include <utility>
#include <QtCore/QFile>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QCoreApplication>
#include <QtExCore/Logging>

namespace QtEx
{
  MonoJsonSettingsProvider::MonoJsonSettingsProvider(Qt::Object* parent) noexcept
    : ISettingsProvider(parent)
    , m_filepath(QCoreApplication::applicationDirPath() + DEFAULT_FILEPATH)
    , m_fallback_file(DEFAULT_FALLBACK_RC_FILE)
  {
    qRegisterMetaType<MonoJsonSettingsProvider*>("MonoJsonSettingsProvider*");
  }

  MonoJsonSettingsProvider::MonoJsonSettingsProvider(String filepath, String fallback_file, Qt::Object* parent) noexcept
    : ISettingsProvider(parent)
    , m_filepath(std::move(filepath))
    , m_fallback_file(std::move(fallback_file))
  {
    qRegisterMetaType<MonoJsonSettingsProvider*>("MonoJsonSettingsProvider*");
  }

  QVariant MonoJsonSettingsProvider::read(const QString& key, const QString& fid) const noexcept
  {
    (void)fid;
    if(not m_json.count(key))
      return {};
    return m_json.at(key);
  }

  void MonoJsonSettingsProvider::write(const String& key, const Variant& value, const String& fid) noexcept
  {
    (void)fid;
    m_json[key] = value;
  }

  void MonoJsonSettingsProvider::load() noexcept
  {
    Log::log(Debug) << scope_information << "Loading settings";
    QFile file(m_filepath);
    if(not file.exists())
      QFile::copy(m_fallback_file, m_filepath);
    file.setPermissions(QFileDevice::ReadUser | QFileDevice::WriteUser);
    if(not file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
      Log::log(Error) << scope_information << "Failed to open file for read:" << m_filepath;
      return;
    }

    auto doc = QJsonDocument::fromJson(file.readAll());
    file.close();

    if(not doc.isNull() and doc.isObject())
    {
      auto json = doc.object();
      for(auto it = json.begin(); it != json.end(); ++it)
        m_json.insert({it.key(), it.value().toVariant()});
    }
  }

  void MonoJsonSettingsProvider::save() const noexcept
  {
    Log::log(Debug) << scope_information << "Saving settings";
    auto data = QJsonDocument(QJsonObject::fromVariantMap(QMap<String, Variant>(m_json))).toJson(QJsonDocument::JsonFormat::Indented);
    QFile::remove(m_filepath);
    QFile file(m_filepath);
    if(not file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
      Log::log(Error) << scope_information << "Failed to open file for write:" << m_filepath;
      return;
    }
    file.write(data);
    file.close();
  }
} // QtEx