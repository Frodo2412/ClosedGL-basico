#pragma once

#include <vector>
#include "../raster/pixel.h"

struct image
{
    int width, height;
    std::vector<pixel> pixels;
    image() = default;
    explicit image(int width, int height, std::vector<pixel>& vector);


    static color background_color;
};
