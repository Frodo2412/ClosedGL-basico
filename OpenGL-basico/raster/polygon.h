#pragma once
#include <vector>

#include "color.h"
#include "../raster/line.h"
#include "shape.h"

struct polygon : shape
{
    std::vector<line> edges;
    color fill_color;

    explicit polygon(std::vector<line> edges, color fill_color);
};
