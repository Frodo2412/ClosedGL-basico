#pragma once

#include <vector>
#include "pixel.h"
#include "projection.h"

struct image
{
    int width, height;
    std::vector<pixel> pixels;
    image() = default;
    explicit image(int width, int height, std::vector<pixel>& vector);
};
