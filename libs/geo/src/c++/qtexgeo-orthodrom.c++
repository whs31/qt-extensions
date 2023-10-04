//
// Created by whs31 on 29.09.23.
//

#include "qtexgeo-orthodrom.h"
#include <QtExCore/Math>

namespace QtEx
{
  Orthodrom::Orthodrom()
    : m_a({0, 0})
    , m_b({0, 0})
    , m_a1(0)
    , m_a2(0)
  {}

  Orthodrom::Orthodrom(const GeoCoordinate& a, const GeoCoordinate& b)
    : m_a(a)
    , m_b(b)
    , m_a1(tg(deg2rad(a.latitude())) / sin(deg2rad(b.longitude() - a.longitude())))
    , m_a2(tg(deg2rad(b.latitude())) / sin(deg2rad(b.longitude() - a.longitude())))
  {
    this->distribute();
  }

  QList<Variant> Orthodrom::get() const noexcept
  {
    if(compare<double>(sin(m_a.longitude() - m_b.longitude()), 0))
      return m_path;
    return { QVariant::fromValue(m_a), QVariant::fromValue(m_b) };
  }

  void Orthodrom::set(const GeoCoordinate& a, const GeoCoordinate& b) noexcept
  {
    m_a = a;
    m_b = b;
    m_a1 = tg(deg2rad(a.latitude())) / sin(deg2rad(b.longitude() - a.longitude()));
    m_a2 = tg(deg2rad(b.latitude())) / sin(deg2rad(b.longitude() - a.longitude()));

    this->distribute();
  }

  double Orthodrom::latitudeAt(double longitude) const noexcept {
    return rad2deg(atan(m_a2 * sin(deg2rad(longitude - m_a.longitude())) + m_a1 * sin(deg2rad(m_b.longitude() - longitude))));
  }

  void Orthodrom::distribute() noexcept
  {
    if(compare<double>(m_a1, 0) or compare<double>(m_a2, 0))
      return;
    m_path.clear();
    m_path << Variant::fromValue(m_b);
    auto α = m_a.azimuthTo(m_b);
    auto ⅆ = distance();
    while(ⅆ - 10 > 0)
    {
      GeoCoordinate t = m_a.atDistanceAndAzimuth(ⅆ * 1'000, α);
      m_path << Variant::fromValue(GeoCoordinate(latitudeAt(t.longitude()), t.longitude(), 0));
      ⅆ -= 10;
    }

    GeoCoordinate t = m_a.atDistanceAndAzimuth(ⅆ, α);
    if(not compare<double>(t.longitude() - m_b.longitude(), 0))
      m_path << Variant::fromValue(GeoCoordinate(latitudeAt(t.longitude()), t.longitude(), 0));
    else
      m_path << Variant::fromValue(t);
  }

  double Orthodrom::distance() const noexcept {
    return rad2deg(acos(sin(deg2rad(m_a.latitude())) * sin(deg2rad(m_b.latitude())) + cos(deg2rad(m_a.latitude()))
           * cos(deg2rad(m_b.latitude())) * cos(deg2rad(m_b.longitude() - m_a.longitude())))) * 60 * 1.853;
  }
} // QtEx