#pragma once
#include "color.h"
#include "point.h"

struct pixel
{
    point point;
    color color;

    pixel(::point point, ::color color);
    pixel(): point(0, 0), color(0, 0, 0) {}
};
