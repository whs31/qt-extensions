// 26.09.2023 by whs31

#pragma once

#include <memory>
#include <cstdint>
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
#if defined(QTEX_CORE_MAKE_PUBLIC_ALIAS_FOR_QT_CLASSES)
namespace QtEx {
#endif
  using String = QString;
  using Object = QObject;
  using ByteArray = QByteArray;
  using Color = QColor;
  using Variant = QVariant;

  using namespace tl;
  using std::unique_ptr;
  using std::shared_ptr;
  using std::weak_ptr;
#if defined(QTEX_CORE_MAKE_PUBLIC_ALIAS_FOR_QT_CLASSES)
} // QtEx
#endif

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;
using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using usize = size_t;
using isize = int;
using uptr = uintptr_t;
using iptr = ptrdiff_t;
using f32 = float;
using f64 = double;

#define as_const qAsConst

#if defined(QTEX_CORE_ENABLE_TESTS)
// if needed
#endif

#if !defined(invokable)
#   define invokable Q_INVOKABLE
#else
#   error "QtEx Core defined <invokable>, but it is defined somewhere already."
#endif