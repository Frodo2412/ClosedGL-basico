#pragma once
#include <vector>

#include "color.h"
#include "line.h"
#include "../geometry/vector2.h"

struct polygon
{
    std::vector<vector2> vertices; // assume ordered, non-intersecting, non-overlapping
    color fill_color;

    std::vector<line> get_lines() const;

    explicit polygon(std::vector<vector2> vertices, color fill_color);

};
