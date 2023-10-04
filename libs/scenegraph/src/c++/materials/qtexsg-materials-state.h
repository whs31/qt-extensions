//
// Created by whs31 on 28.09.23.
//

#pragma once

#include <QtGui/QColor>

struct State
{
  int compare(const State*) const;
  QColor color;
};

inline int State::compare(const State* other) const
{
  if(color.rgba() == other->color.rgba())
    return 0;
  if(color.rgba() < other->color.rgba())
    return -1;
  return 1;
}