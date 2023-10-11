//
// Created by whs31 on 29.09.23.
//

#pragma once

#include <QtPositioning/QGeoCoordinate>
#include <QtExGeo/Math>

namespace QtEx
{
  struct GraphPoint
  {
    GraphPoint();
    GraphPoint(float d, float h);

    float distance;          ///< Расстояние точки от нуля в метрах.
    float elevation;         ///< Высота точки в метрах.
  };

  struct IntersectionPoint
  {
    /// \brief Перечисление состояний пересечения с землей.
    enum Intersection
    {
      NonIntersecting,        ///< Точка не пересекается с землей.
      IntersectingIn,         ///< Точка пересекается с землей. Предыдущая точка не пересекалась с землей.
      IntersectingOut,        ///< Точка пересекается с землей. Следующая точка не пересекается с землей.
      InsideGround            ///< Точка лежит внутри рельефа. Соседние точки пересекаются с землей либо лежат внутри рельефа.
    };

    IntersectionPoint();
    IntersectionPoint(double altitude, double distance, bool base, Intersection state, GeoCoordinate coord = GeoCoordinate());

    double altitude;          ///< Высота точки в метрах.
    double distance;          ///< Расстояние точки от нуля в метрах.
    bool base;                ///< Является ли точка базовой (исходной) точкой пути, или она появилась в результате пересечения с рельефом.
    Intersection state;       ///< Состояние пересечения.
    GeoCoordinate coordinate;
  };
} // QtEx

namespace QtEx
{
  inline GraphPoint::GraphPoint()
    : distance(0)
    , elevation(0)
  {}

  inline GraphPoint::GraphPoint(float d, float h)
    : distance(d)
    , elevation(h)
  {}

  inline IntersectionPoint::IntersectionPoint()
    : altitude(0)
    , distance(0)
    , base(false)
    , state(NonIntersecting)
  {}

  inline IntersectionPoint::IntersectionPoint(double altitude, double distance, bool base, Intersection state, GeoCoordinate coord)
    : altitude(altitude)
    , distance(distance)
    , base(base)
    , state(state)
    , coordinate(coord)
  {}
} // QtEx

