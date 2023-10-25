#pragma once

#include <QtExtensions/Global>

namespace QtEx
{
  class Point1D
  {
    Q_GADGET
    Q_PROPERTY(float x READ x WRITE setX FINAL)

    public:
      explicit Point1D() noexcept;
      explicit Point1D(float x) noexcept;

      [[nodiscard]] float x() const noexcept;      void setX(float) noexcept;
      [[nodiscard]] float& refX() noexcept;

    private:
      float m_x;
  };
} // QtEx

Q_DECLARE_METATYPE(QtEx::Point1D)