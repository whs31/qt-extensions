//
// Created by whs31 on 29.09.23.
//

#pragma once

#include <QtCore/QObject>
#include <QtExtensions/Global>

using Qt::Object;
using Qt::String;

namespace QtEx
{
  class GoogleMapsProvider : public Object
  {
    Q_OBJECT
    Q_PROPERTY(QString path READ path WRITE setPath FINAL)
    // @todo source path

    public:
      explicit GoogleMapsProvider(Object* parent = nullptr);

      [[nodiscard]] String path() const;      void setPath(const String&);

    private:
      void create() noexcept;
      // @todo cleanup

    private:
      String m_path;
  };
} // QtEx
