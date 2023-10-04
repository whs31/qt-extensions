// 26.09.2023 by whs31

#pragma once

#include <utility>
#include <type_traits>
#include <QtCore/QtGlobal>
#include <QtCore/QMetaType>
#include <tl/expected.hpp>

namespace QtEx
{
  template<typename T>
  using enable_if_decimal = std::enable_if_t<std::is_floating_point_v<T>, T>;

  template<typename T>
  using enable_if_decimal_logic = std::enable_if_t<std::is_floating_point<T>::value, bool>;
} // QtEx

#if defined(QTEX_CORE_USE_DOUBLE)
  using decimal = double;
#else
  using decimal = float;
#endif

class QObject;
class QColor;
class QVariant;
#if !defined(QTEX_CORE_MAKE_PUBLIC_ALIAS_FOR_QT_CLASSES)
namespace QtEx {
#endif
  using String = QString;
  using Object = QObject;
  using ByteArray = QByteArray;
  using Color = QColor;
  using Variant = QVariant;

  template<class T, class E>
  using Expected = tl::expected<T, E>;

  template<class E>
  using Unexpected = tl::unexpected<E>;

  using namespace tl;
#if !defined(QTEX_CORE_MAKE_PUBLIC_ALIAS_FOR_QT_CLASSES)
} // QtEx
#endif

#if defined(QTEX_CORE_ENABLE_TESTS)
// if needed
#endif

#if !defined(invokable)
#   define invokable Q_INVOKABLE
#else
#   error "QtEx Core defined <invokable>, but it is defined somewhere already."
#endif