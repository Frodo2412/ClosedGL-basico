#pragma once
#include <vector>

#include "line.h"
#include "pixel.h"

class mid_point_algorithm
{
public:
    static std::vector<point> raster(const line& line);
};
