//
// Created by whs31 on 29.09.23.
//

#pragma once

#include <QtCore/QVariantList>
#include <QtPositioning/QGeoCoordinate>
#include <QtExCore/Global>
#include <QtExGeo/Math>

using Qt::Variant;
using Qt::GeoCoordinate;

namespace QtEx
{
  class Orthodrom
  {
    public:
      Orthodrom();
      Orthodrom(const GeoCoordinate& a, const GeoCoordinate& b);

      [[nodiscard]] QList<Variant> get() const noexcept;
      void set(const GeoCoordinate& a, const GeoCoordinate& b) noexcept;

      double latitudeAt(double longitude) const noexcept;

    private:
      void distribute() noexcept;
      double distance() const noexcept;

    private:
      double m_a1, m_a2;
      GeoCoordinate m_a, m_b;
      QList<Variant> m_path;
  };
} // QtEx
