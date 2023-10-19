//
// Created by whs31 on 28.09.23.
//

#pragma once

#include <QtCore/QString>
#include "QtExCore/Global"

using Qt::String;

namespace QtEx
{
  class INameable
  {
    public:
      INameable();
      explicit INameable(String);

      [[nodiscrad]] String name() const;
      virtual void setName(const String&);

    protected:
      String m_name;
  };
} // QtEx

namespace QtEx
{
  inline INameable::INameable()
    : m_name(String())
  {}

  inline INameable::INameable(String q)
    : m_name(std::move(q))
  {}

  inline String INameable::name() const { return m_name; }
  inline void INameable::setName(const String& q) { m_name = q; }
} // QtEx