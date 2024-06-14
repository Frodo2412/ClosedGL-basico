#pragma once

#include "SDL.h"

#include "image.h"

class renderer
{
public:
    static void render_image(image& image, SDL_Renderer* renderer);
    static void render_intermedium_image(image& img, SDL_Renderer* renderer);
};
