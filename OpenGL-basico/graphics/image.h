#pragma once

#include <SDL_stdinc.h>
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
    int get_width();
    int get_height();
    pixel get_pixel(int x, int y);
    std::vector<Uint32> get_pixel_data();
};
