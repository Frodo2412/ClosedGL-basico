#pragma once

#include <vector>

#include "../raster/polygon.h"

struct projection
{
    std::vector<polygon> shapes;
    explicit projection(std::vector<polygon> shapes);
};
