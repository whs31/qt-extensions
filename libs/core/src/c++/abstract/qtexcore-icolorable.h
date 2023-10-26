//
// Created by whs31 on 28.09.23.
//

#pragma once

#include <QtGui/QColor>
#include <QtExtensions/Global>

using Qt::Color;

namespace QtEx
{
  class IColorable
  {
    public:
      IColorable();
      explicit IColorable(Color);

      [[nodiscard]] Color color() const;
      virtual void setColor(const Color&);

    protected:
      Color m_color;
  };
} // QtEx

namespace QtEx
{
  inline IColorable::IColorable()
    : m_color(Color ())
  {}

  inline IColorable::IColorable(Color q)
    : m_color(std::move(q))
  {}

  inline Color IColorable::color() const { return m_color; }
  inline void IColorable::setColor(const Color& q) { m_color = q; }
} // QtEx