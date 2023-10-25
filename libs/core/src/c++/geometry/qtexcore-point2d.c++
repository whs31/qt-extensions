#include "qtexcore-point2d.h"
#include <QtCore/QPointF>
#include <QtCore/QDebug>
#include <QtExtensions/Math>

namespace QtEx
{
  Point2D::Point2D() noexcept
    : Point1D()
    , m_y(0)
  {}

  Point2D::Point2D(float x, float y) noexcept
    : Point1D(x)
    , m_y(y)
  {}

  Point2D::Point2D(const QPointF& q) noexcept
    : Point1D(static_cast<float>(q.x()))
    , m_y(static_cast<float>(q.y()))
  {}

  float Point2D::y() const noexcept { return m_y; }
  void Point2D::setY(float q) noexcept { m_y = q; }
  float& Point2D::refY() noexcept { return m_y; }

  bool Point2D::null() const noexcept { return is_null(x()) or is_null(y()); }
  float Point2D::manhattanLengthTo(const Point2D& q) const noexcept{ return abs(x() - q.x()) + abs(y() - q.y()); }
  float Point2D::manhattanLengthToOrigin() const noexcept { return manhattanLengthTo({0, 0}); }
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wwrong-order-arguments" // need name of warning idc
  Point2D Point2D::inverted() const noexcept { return { y(), x()}; }
  #pragma clang diagnostic pop
  Point2D Point2D::atAngleAndRadius(float angle, float radius) const noexcept {
    return { x() + cos(deg2rad(angle)) * radius, y() + sin(deg2rad(angle)) * radius };
  }
  QPointF Point2D::toQPointF() const noexcept { return { x(), y() }; }
  Point2D& Point2D::invert() noexcept {
    auto q = x();
    this->setX(y());
    this->setY(q);
    return *this;
  }

  Point2D Point2D::fromQPointF(const QPointF& point) noexcept { return { static_cast<float>(point.x()), static_cast<float>(point.y()) }; }
  float Point2D::scalarProduct(const Point2D& first, const Point2D& second) noexcept { return first.x() * second.x() + first.y() * second.y(); }
  float Point2D::distanceBetween(const Point2D& first, const Point2D& second) noexcept { return hypotenuse(second.x() - first.x(), second.y() - first.y()); }
  float Point2D::angleBetween(const Point2D& first, const Point2D& second) noexcept {
    return rad2deg<float>(static_cast<float>(atan2(abs(second.y() - first.y()), abs(second.x() - first.x()))));
  }

  Point2D& Point2D::operator+=(const Point2D& point) {
    refX() += point.x();
    refY() += point.y();
    return *this;
  }

  Point2D& Point2D::operator-=(const Point2D& point) {
    refX() -= point.x();
    refY() -= point.y();
    return *this;
  }

  Point2D& Point2D::operator*=(float f) {
    refX() *= f;
    refY() *= f;
    return *this;
  }

  Point2D& Point2D::operator/=(float f) {
    refX() /= f;
    refY() /= f;
    return *this;
  }

  Point2D& Point2D::operator=(const Point2D& other) {
    if(this == &other)
      return *this;
    setX(other.x());
    setY(other.y());
    return *this;
  }

  bool operator==(const Point2D& p1, const Point2D& p2) {
    bool q = std::isnan(p1.x()) or std::isnan(p1.y()) or std::isnan(p2.x()) or std::isnan(p2.y());
    return not q and p1.x() == p2.x() and p1.y() == p2.y();
  }

  bool operator!=(const Point2D& p1, const Point2D& p2) { return not (p1 == p2); }
  Point2D operator+(const Point2D& p1, const Point2D& p2) { return { p1.x() + p2.x(), p1.y() + p2.y()}; }
  Point2D operator+(const Point2D& p) { return p; }
  Point2D operator-(const Point2D& p1, const Point2D& p2) { return { p1.x() - p2.x(), p1.y() - p2.y()}; }
  Point2D operator-(const Point2D& p) { return { -p.x(), -p.y()}; }
  Point2D operator*(float f, const Point2D& p) { return { p.x() * f, p.y() * f}; }
  Point2D operator*(const Point2D& p, float f) { return { p.x() * f, p.y() * f}; }
  Point2D operator/(const Point2D& p, float f) { return { p.x() / f, p.y() / f}; }

  QDebug operator<<(QDebug d, const Point2D& p) {
    d.nospace() << "Point2D(" << p.x() << ", " << p.y() << ")";
    return d;
  }
} // QtEx