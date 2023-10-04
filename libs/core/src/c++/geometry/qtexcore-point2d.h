#pragma once

#include "QtExCore/Global"
#include "QtExCore/Point1D"

class QPointF;
class QDebug;

namespace QtEx
{
  class Point2D : public Point1D
  {
    Q_GADGET
    Q_PROPERTY(float y READ y WRITE setY FINAL)

    public:
      Point2D() noexcept;
      Point2D(float x, float y) noexcept;
      explicit Point2D(const QPointF&) noexcept;

      [[nodiscard]] float y() const noexcept;   void setY(float) noexcept;
      [[nodiscard]] float& refY() noexcept;

      [[nodiscard]] bool null() const noexcept;
      [[nodiscard]] float manhattanLengthTo(const Point2D&) const noexcept;
      [[nodiscard]] float manhattanLengthToOrigin() const noexcept;
      [[nodiscard]] Point2D inverted() const noexcept;
      [[nodiscard]] Point2D atAngleAndRadius(float angle, float radius) const noexcept;
      [[nodiscard]] QPointF toQPointF() const noexcept;

      Point2D& invert() noexcept;

      friend bool operator==(const Point2D&, const Point2D&);
      friend bool operator!=(const Point2D&, const Point2D&);
      friend Point2D operator+(const Point2D&, const Point2D&);
      friend Point2D operator-(const Point2D& p1, const Point2D& p2);
      friend Point2D operator+(const Point2D&);
      friend Point2D operator-(const Point2D&);
      friend Point2D operator*(float, const Point2D&);
      friend Point2D operator*(const Point2D&, float);
      friend Point2D operator/(const Point2D&, float);
      Point2D& operator+=(const Point2D& point);
      Point2D& operator-=(const Point2D& point);
      Point2D& operator*=(float f);
      Point2D& operator/=(float f);
      Point2D& operator=(const Point2D& other);
      friend QDebug operator<<(QDebug d, const Point2D& p);

    public:
      static Point2D fromQPointF(const QPointF& point) noexcept;
      static float scalarProduct(const Point2D& first, const Point2D& second) noexcept;
      static float distanceBetween(const Point2D& first, const Point2D& second) noexcept;
      static float angleBetween(const Point2D& first, const Point2D& second) noexcept;

    private:
      float m_y;
  };
} // QtEx

Q_DECLARE_METATYPE(QtEx::Point2D)