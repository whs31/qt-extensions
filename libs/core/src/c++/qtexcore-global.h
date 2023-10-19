// 26.09.2023 by whs31

#pragma once

#include <memory>
#include <QtCore/QtGlobal>
#include <QtCore/QMetaType>
#include <Backbone/Global>

#if defined(QTEX_CORE_USE_DOUBLE)
  using decimal = double;
#else
  using decimal = float;
#endif

#if defined(QTEX_CORE_ENABLE_TESTS)
// if needed
#endif