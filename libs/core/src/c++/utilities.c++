//
// Created by whs31 on 10/31/2023.
//

#include "utilities.h"
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QUrl>

using Qt::Directory;
using Qt::File;
using Qt::String;

namespace QtEx::Utility
{
  auto emplaceFile(const String& target, const String& fallback, EmplaceMode mode) noexcept -> bool
  {
    auto target_filename = target;
    const auto target_folder = target_filename.remove(QUrl(target).fileName());
    Directory directory(target_folder);
    if(not directory.exists())
      directory.mkpath(target_folder);

    File file(target);
    bool ret = true;
    if(not file.exists() or mode == EmplaceMode::Always)
      ret = File::copy(fallback, target);
    return ret;
  }
} // QtEx::Utility