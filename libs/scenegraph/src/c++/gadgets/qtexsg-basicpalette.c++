//
// Created by whs31 on 28.09.23.
//

#include "qtexsg-basicpalette.h"

namespace QtEx
{
  BasicPalette::BasicPalette()
    : m_background("black")
    , m_foreground("white")
    , m_overlay("gray")
    , m_overlay2("#777777")
    , m_accent("green")
    , m_warn("yellow")
    , m_error("red")
    , m_info("blue")
  {}

  Color BasicPalette::background() const { return m_background; }
  void BasicPalette::setBackground(const Color& x) { m_background = x; }

  Color BasicPalette::foreground() const { return m_foreground; }
  void BasicPalette::setForeground(const Color& x) { m_foreground = x; }

  Color BasicPalette::overlay() const { return m_overlay; }
  void BasicPalette::setOverlay(const Color& x) { m_overlay = x; }

  Color BasicPalette::overlay2() const { return m_overlay2; }
  void BasicPalette::setOverlay2(const Color& x) { m_overlay2 = x; }

  Color BasicPalette::accent() const { return m_accent; }
  void BasicPalette::setAccent(const Color& x) { m_accent = x; }

  Color BasicPalette::warn() const { return m_warn; }
  void BasicPalette::setWarn(const Color& x) { m_warn = x; }

  Color BasicPalette::error() const { return m_error; }
  void BasicPalette::setError(const Color& x) { m_error = x; }

  Color BasicPalette::info() const { return m_info; }
  void BasicPalette::setInfo(const Color& x) { m_info = x; }
} // QtEx