#pragma once

#include "image.h"
#include "SDL.h"

class renderer
{
public:
    static int loaded_;
    static void render_image(image& image);
    static void render_intermedium_image(image& img, int max_x, SDL_Renderer* renderer);
};
