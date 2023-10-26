//
// Created by whs31 on 28.09.23.
//

#include "qtexcore-logging.h"
#include <QtCore/QCoreApplication>
#include <Libra/Platform>

#if QT_VERSION_MAJOR >= 6
#include <QtCore/QRegularExpression>
#endif

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

  void Log::printPlatformInfo() noexcept
  {
    llog(Info) "Platform architecture:\t\t" <<
    #if defined(LIBRA_ARCH_X86_32)
    "x86-32"
    #elif defined(LIBRA_ARCH_X86_64)
    "x86-64"
    #elif defined(LIBRA_ARCH_ALPHA)
    "Alpha"
    #elif defined(LIBRA_ARCH_ARM)
    "ARM"
    #elif defined(LIBRA_ARCH_BLACKFIN)
    "Blackfin"
    #elif defined(LIBRA_ARCH_CONVEX)
    "Convex"
    #elif defined(LIBRA_ARCH_ELBRUS2000)
    "Elbrus 2000"
    #elif defined(LIBRA_ARCH_IA64)
    "Itanium64"
    #elif defined(LIBRA_ARCH_LOONGARCH)
    "LoongArch"
    #elif defined(LIBRA_ARCH_M68K)
    "Motorola 68000"
    #elif defined(LIBRA_ARCH_MIPS)
    "MIPS"
    #elif defined(LIBRA_ARCH_PARISC)
    "PA RISC"
    #elif defined(LIBRA_ARCH_POWERPC)
    "PowerPC"
    #elif defined(LIBRA_ARCH_PTX)
    "PTX"
    #elif defined(LIBRA_ARCH_PYRAMID)
    "Pyramid"
    #elif defined(LIBRA_ARCH_RISCV)
    "RISC V"
    #elif defined(LIBRA_ARCH_RS6000)
    "RS6000"
    #elif defined(LIBRA_ARCH_SPARC)
    "Sparc"
    #elif defined(LIBRA_ARCH_SUPERH)
    "SuperH"
    #elif defined(LIBRA_ARCH_SYS370)
    "System370"
    #elif defined(LIBRA_ARCH_SYS390)
    "System390"
    #elif defined(LIBRA_ARCH_Z_ARCHITECTURE)
    "Z Architecture"
    #elif defined(LIBRA_ARCH_UNKNOWN)
    "Unknown!"
    #endif
    ;

    llog(Info) "Platform compiler:\t\t" <<
    #if defined(LIBRA_COMPILER_BORLAND)
    "Borland C"
    #elif defined(LIBRA_COMPILER_CLANG)
    "Clang"
    #elif defined(LIBRA_COMPILER_COMO)
    "Como"
    #elif defined(LIBRA_COMPILER_COMPAQ)
    "Compaq"
    #elif defined(LIBRA_COMPILER_DIAB)
    "Diab"
    #elif defined(LIBRA_COMPILER_DIGITAL_MARS)
    "Digital Mars"
    #elif defined(LIBRA_COMPILER_DIGNUS)
    "Dignus Systems"
    #elif defined(LIBRA_COMPILER_EDG)
    "EDG"
    #elif defined(LIBRA_COMPILER_PATHSCALE)
    "Pathscale"
    #elif defined(LIBRA_COMPILER_GNU)
    "GNU GCC"
    #elif defined(LIBRA_COMPILER_GREENHILLS)
    "GreenHills"
    #endif
    ;

    llog(Info) "Platform endianness:\t\t" <<
    #if defined(LIBRA_ENDIAN_BIG)
    "Big"
    #elif defined(LIBRA_ENDIAN_LITTLE)
    "Little"
    #elif defined(LIBRA_ENDIAN_UNKNOWN)
    "Unknown!"
    #endif
    ;

    llog(Info) "Platform C++ version:\t\t" <<
    #if defined(LIBRA_CXX_PRE98)
    "Pre C++98 or older"
    #elif defined(LIBRA_CXX_98)
    "C++98"
    #elif defined(LIBRA_CXX_03)
    "C++03"
    #elif defined(LIBRA_CXX_11)
    "C++11"
    #elif defined(LIBRA_CXX_14)
    "C++14"
    #elif defined(LIBRA_CXX_17)
    "C++17"
    #elif defined(LIBRA_CXX_20)
    "C++20"
    #elif defined(LIBRA_CXX_23)
    "C++23 or newer"
    #endif
    ;

    llog(Info) "Platform operating system:\t" <<
    #if defined(LIBRA_OS_WINDOWS)
    "Microsoft Windows"
    #elif defined(LIBRA_OS_LINUX)
    "GNU/Linux"
    #elif defined(LIBRA_OS_MACOS)
    "Apple MacOS"
    #elif defined(LIBRA_OS_ANDROID)
    "Android"
    #elif defined(LIBRA_OS_IOS)
    "Apple IOS"
    #elif defined(LIBRA_OS_CYGWIN)
    "Cygwin"
    #elif defined(LIBRA_OS_FREEBSD)
    "FreeBSD"
    #elif defined(LIBRA_OS_DRAGONFLY)
    "DragonFly"
    #elif defined(LIBRA_OS_NETBSD)
    "NetBSD"
    #elif defined(LIBRA_OS_OPENBSD)
    "OpenBSD"
    #elif defined(LIBRA_OS_UNRECOGNIZED)
    "Unknown!"
    #endif
    ;

    llog(Info) "Platform word size:\t\t" << LIBRA_WORD_SIZE;
  }

  void Log::printQtInfo() noexcept
  {
    llog(Info) "Qt Version:\t\t\t\t" << Libra::Platform::qtVersion();
  }

  void Log::printApplicationInfo(QCoreApplication* app) noexcept
  {
    llog(Info) "Application name:\t\t" << app->applicationName();
    llog(Info) "Application version:\t" << app->applicationVersion();
    llog(Info) "Application vendor:\t\t" << app->organizationName();
    llog(Info) "\t\t\t\t" << app->organizationDomain();
    llog(Info) "Application path:\t\t" << app->applicationFilePath();
    llog(Info) "Application PID:\t\t" << app->applicationPid();
  }

  void Log::linebreak() noexcept { llog_no_trace(Debug) ""; }

  const char* Private::parseScopeInfo(const char* x) noexcept
  {
    #if QT_VERSION_MAJOR <= 5
    QRegExp r(".* ([^\\s]*)\\(");
    #else
    QRegularExpression r(".* ([^\\s]*)\\(");
    #endif

    #if QT_VERSION_MAJOR <= 5
    r.lastIndexIn(x);
    return r.capturedTexts()
            .back()
            .replace("::", Log::separator())
            .append(":")
            //.append("\t")
            .toLocal8Bit()
            .data();
    #else
    return r.match(x)
            .capturedTexts()
            .back()
            .replace("::", Log::separator())
            .append(":")
            //.append("\t")
            .toLocal8Bit()
            .data();
    #endif
  }
} // QtEx
