//
// Created by whs31 on 28.09.23.
//

#pragma once

#include <QtGui/QColor>
#include <QtExCore/Global>

namespace QtEx
{
  class BasicPalette
  {
    Q_GADGET
      Q_PROPERTY(QColor background READ background WRITE setBackground)
      Q_PROPERTY(QColor foreground READ foreground WRITE setForeground)
      Q_PROPERTY(QColor overlay READ overlay WRITE setOverlay)
      Q_PROPERTY(QColor overlay2 READ overlay2 WRITE setOverlay2)
      Q_PROPERTY(QColor accent READ accent WRITE setAccent)
      Q_PROPERTY(QColor warn READ warn WRITE setWarn)
      Q_PROPERTY(QColor error READ error WRITE setError)
      Q_PROPERTY(QColor info READ info WRITE setInfo)

    public:
      BasicPalette();

      [[nodiscard]] Color background() const; void setBackground(const Color&);
      [[nodiscard]] Color foreground() const; void setForeground(const Color&);
      [[nodiscard]] Color overlay() const; void setOverlay(const Color&);
      [[nodiscard]] Color overlay2() const; void setOverlay2(const Color&);
      [[nodiscard]] Color accent() const; void setAccent(const Color&);
      [[nodiscard]] Color warn() const; void setWarn(const Color& color);
      [[nodiscard]] Color error() const; void setError(const Color& color);
      [[nodiscard]] Color info() const; void setInfo(const Color& color);

    private:
      Color m_background;
      Color m_foreground;
      Color m_overlay;
      Color m_overlay2;
      Color m_accent;
      Color m_warn;
      Color m_error;
      Color m_info;
  };
} // QtEx

Q_DECLARE_METATYPE(QtEx::BasicPalette)