//
// Created by whs31 on 28.09.23.
//

#include "qtexsg-scenegraphobject.h"
#include <QtQuick/QSGNode>

namespace QtEx
{
  ScenegraphObject::ScenegraphObject(QQuickItem* parent)
    : QQuickItem(parent)
    , m_require_recolor(false)
  {
    this->setFlag(ItemHasContents);
  }

  QSGNode* ScenegraphObject::createNode() { return new QSGNode; }
  bool ScenegraphObject::recolor() const { return m_require_recolor; }
  void ScenegraphObject::requireRecolor()
  {
    m_require_recolor = true;
    this->update();
  }
  void ScenegraphObject::fulfillRecolor() { m_require_recolor = false; }

  QSGNode* ScenegraphObject::updatePaintNode(QSGNode* node, QQuickItem::UpdatePaintNodeData*)
  {
    if(node == nullptr)
    {
      node = this->createNode();
      this->setupChildNodes(node);
    }

    if(recolor())
      this->setupNodeColors(node);

    this->drawCall(node);
    for(int i = 0; i < node->childCount(); i++)
      node->childAtIndex(i)->markDirty(recolor() ? (QSGNode::DirtyGeometry | QSGNode::DirtyMaterial) : QSGNode::DirtyGeometry);
    node->markDirty(QSGNode::DirtyGeometry | QSGNode::DirtyMaterial);
    return node;
  }
} // QtEx