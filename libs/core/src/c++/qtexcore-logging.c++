//
// Created by whs31 on 28.09.23.
//

#include "qtexcore-logging.h"


namespace QtEx
{
  String Log::m_separator = ".";

  void Log::setLoggingPattern() noexcept
  {
    qSetMessagePattern("[%{time process}] "
                       "%{if-debug}\033[01;38;05;15m%{endif}"
                       "%{if-info}\033[01;38;05;146m%{endif}"
                       "%{if-warning}\033[1;33m%{endif}"
                       "%{if-critical}\033[1;31m%{endif}"
                       "%{if-fatal}FATAL ERROR \033[1;31m%{endif}%{message}\033[0m");
  }

  void Log::setLoggingPattern(const String& pattern) noexcept { qSetMessagePattern(pattern); }

  String Log::separator() { return m_separator; }
  void Log::setSeparator(const String& x) { m_separator = x; }

  QDebug Log::log(LoggingMode mode) noexcept
  {
    switch(mode)
    {
      case Info: return qInfo();
      case Warning: return qWarning();
      case Error: return qCritical();
      case Debug:
      default: return qDebug();
    }
  }

  QDebug Log::info() noexcept { return log(Info); }
  QDebug Log::warn() noexcept { return log(Warning); }
  QDebug Log::panic() noexcept { return log(Error); }

  const char* Private::parseScopeInfo(const char* x) noexcept
  {
    QRegExp r(".* ([^\\s]*)\\(");
    r.lastIndexIn(x);
    return r.capturedTexts()
            .back()
            .replace("::", Log::separator())
            .prepend("\033[4;2m")
            .append("\033[24;22m")
            .append(":")
            //.append("\t")
            .toLocal8Bit()
            .data();
  }
} // QtEx
