#pragma once
#include <vector>
#include "Point.h"
struct IDrawable
{
    virtual ~IDrawable() {}
    std::vector<DrawablePoint> virtual GetDrawableBuffer() = 0;
};