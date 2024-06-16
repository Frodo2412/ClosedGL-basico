#pragma once

#include "SDL.h"

#include "image.h"

class renderer
{
public:
    static bool loaded_;
    static void render_image(image& image);
    static void render_intermedium_image(image& img, int max_x, SDL_Renderer* renderer);
};
