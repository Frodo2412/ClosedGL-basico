#pragma once

#include <vector>
#include "../raster/pixel.h"

struct image
{
    int width, height;
    std::vector<pixel> pixels;
    explicit image(int width, int height, std::vector<pixel>& vector);
};
