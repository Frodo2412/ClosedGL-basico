#pragma once

#include "SDL.h"

#include "image.h"

class renderer
{
public:
    static void render_image(image& image, SDL_Renderer* renderer, SDL_Window* window);
    static void render_intermedium_image(image& img, int max_x, SDL_Renderer* renderer);
};
