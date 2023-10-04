//
// Created by whs31 on 28.09.23.
//

#pragma once

#include <QtQuick/QSGGeometry>
#include <QtQuick/QSGGeometryNode>
#include <QtExCore/Global>

namespace QtEx
{
  enum CreationMode
  {
    GeometryAndMaterial,
    OnlyGeometry,
    OnlyMaterial,
    EmptyNode
  };

  QSGGeometryNode* createSimpleGeometryNode(const Color& color, unsigned int drawing_mode, CreationMode mode = GeometryAndMaterial, float line_width = 1);

  QSGGeometry::Point2D fromTexturedPoint2D(const QSGGeometry::TexturedPoint2D&);
  QSGGeometry::TexturedPoint2D fromPoint2D(const QSGGeometry::Point2D&, float u, float v);
  QSGGeometry::TexturedPoint2D fromPoint2DBounded(const QSGGeometry::Point2D&, double width, double height);
} // QtEx
