#pragma once
#include <vector>

#include "color.h"
#include "line.h"
#include "shape.h"
#include "../geometry/vector2.h"

struct polygon : shape
{
    std::vector<line> edges;
    color fill_color;

    explicit polygon(std::vector<line> edges, color fill_color);
};
