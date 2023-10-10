//
// Created by whs31 on 10.10.2023.
//

#include "qtextk-settings.h"
#include <stdexcept>
#include <QtExCore/Logging>

namespace QtEx
{
  auto Settings::get(ISettingsProvider* provider) -> Settings* { static Settings instance(provider); return &instance; }
  Settings::Settings(ISettingsProvider* provider, Object* parent)
    : Object(parent)
    , m_io(provider)
  {
    if(provider == nullptr)
      throw std::invalid_argument(scope_information_str + " Null provider was passed to constructor");
    this->load();
    qRegisterMetaType<ISettingsProvider*>("ISettingsProvider*");
  }
} // QtEx