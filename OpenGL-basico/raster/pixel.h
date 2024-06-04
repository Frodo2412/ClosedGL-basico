#pragma once
#include "color.h"
#include "point.h"

struct pixel
{
    point point;
    color color_;
    int x_, y_;
    pixel(::point point, ::color color);
    pixel(int x, int y, color color): point(x, y)
    {
        x_ = x;
        y_ = y;
        color_ = color;
    };
    pixel(): point(0, 0), color_(0, 0, 0)
    {
        x_ = 0;
        y_ = 0;
    }
};
