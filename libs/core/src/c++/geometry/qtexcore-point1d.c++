
#include "qtexcore-point1d.h"

namespace QtEx
{
  Point1D::Point1D() noexcept
    : m_x(0)
  {}

  Point1D::Point1D(float x) noexcept
    : m_x(x)
  {}

  float Point1D::x() const noexcept { return m_x; }
  void Point1D::setX(float q) noexcept { m_x = q; }
  float& Point1D::refX() noexcept { return m_x; }
} // QtEx