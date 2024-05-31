﻿#include "viewport.h"


vector2 viewport::transform(const vector2 vector) const
{
    const float x = ((vector.x + 1) / 2) * width_ + origin_.x;
    const float y = ((vector.y + 1) / 2) * height_ + origin_.y;
    const auto res = vector2(x, y);
    return res;
}