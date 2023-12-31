//
// Created by whs31 on 28.09.23.
//

#pragma once

#include <string>
#include <QtCore/QDebug>
#include <QtCore/QString>
#include <QtExtensions/Global>

#define scope_information Qtx::Private::parseScopeInfo(Q_FUNC_INFO)
#define scope_information_str std::string(scope_information)
#define scope_information_qstr String(scope_information)
#define with_trace << scope_information <<

#define llog(Mode) Qtx::Log::log(Qtx:: Mode) << scope_information <<
#define llog_no_trace(Mode) Qtx::Log::log(Qtx:: Mode) <<

using Qt::String;

class QCoreApplication;

namespace QtEx
{
  enum LoggingMode
  {
    Debug,
    Info,
    Warning,
    Error
  };

  class Log
  {
    public:
      static QDebug log(LoggingMode mode = Debug) noexcept;
      static QDebug info() noexcept;
      static QDebug warn() noexcept;
      static QDebug panic() noexcept;

      static void setLoggingPattern() noexcept;
      static void setLoggingPattern(const String& pattern) noexcept;

      static void linebreak() noexcept;
      static void printPlatformInfo() noexcept;
      static void printQtInfo() noexcept;
      static void printApplicationInfo(QCoreApplication*) noexcept;

      [[nodiscard]] static String separator();
      static void setSeparator(const String&);

    private:
      Log() = default;

    private:
      static String m_separator;
  };

  namespace Private
  {
    const char* parseScopeInfo(const char*) noexcept;
  } // Private
} // QtEx