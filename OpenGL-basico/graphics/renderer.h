#pragma once

#include "SDL.h"

#include "image.h"

class renderer
{
public:
    static void render_image(image& image);
    static SDL_Texture* render_intermedium_image(image& img, SDL_Renderer* renderer);
};
