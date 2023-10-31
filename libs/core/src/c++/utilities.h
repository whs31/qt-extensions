//
// Created by whs31 on 10/31/2023.
//

#pragma once

#include <QtExtensions/Global>

namespace QtEx::Utility
{
  enum class EmplaceMode
  {
    OnlyIfMissing,
    Always
  };

  auto emplaceFile(const Qt::String& target, const Qt::String& fallback, EmplaceMode) noexcept -> bool;
} // QtEx::Utility


