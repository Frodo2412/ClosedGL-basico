#pragma once

#include <vector>
#include "../raster/pixel.h"

enum image_type
{
    normal,
    reflectividad,
    refractividad
};

struct image
{
    int width, height;
    enum image_type type_;
    std::vector<pixel> pixels;
    explicit image(int width, int height, std::vector<pixel>& vector, image_type type);
    std::string get_type();
    pixel get_pixel(int x, int y);
};
