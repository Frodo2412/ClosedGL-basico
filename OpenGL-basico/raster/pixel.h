#pragma once
#include "color.h"
#include "point.h"

struct pixel
{
    point point;
    color color;

    pixel(::point point, ::color color);
};
