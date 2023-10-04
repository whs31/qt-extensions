//
// Created by whs31 on 28.09.23.
//

#include "qtexsg-scenegraph-utils.h"
#include <QtQuick/QSGFlatColorMaterial>

namespace QtEx
{
  QSGGeometryNode* createSimpleGeometryNode(const Color& color, unsigned int drawing_mode, CreationMode mode, float line_width)
  {
    auto ret = new QSGGeometryNode;
    if(mode == EmptyNode)
      goto returning;

    if(mode == GeometryAndMaterial or mode == OnlyMaterial)
    {
      auto* material = new QSGFlatColorMaterial;
      material->setColor(color);
      ret->setMaterial(material);
    }
    if(mode == GeometryAndMaterial or mode == OnlyGeometry)
    {
      auto* geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 0, 0, QSGGeometry::UnsignedIntType);
      geometry->setDrawingMode(drawing_mode);
      geometry->setLineWidth(line_width);
      ret->setGeometry(geometry);
    }
    ret->setFlags(QSGNode::OwnsGeometry | QSGNode::OwnsMaterial);

    returning:
      return ret;
  }

  QSGGeometry::Point2D fromTexturedPoint2D(const QSGGeometry::TexturedPoint2D& q) { return QSGGeometry::Point2D({q.x, q.y}); }
  QSGGeometry::TexturedPoint2D fromPoint2D(const QSGGeometry::Point2D& q, float u, float v) { return QSGGeometry::TexturedPoint2D({q.x, q.y, u, v}); }
  QSGGeometry::TexturedPoint2D fromPoint2DBounded(const QSGGeometry::Point2D& q, double width, double height) {
    return QSGGeometry::TexturedPoint2D({q.x, q.y, q.x / static_cast<float>(width), q.y / static_cast<float>(height)});
  }
} // QtEx