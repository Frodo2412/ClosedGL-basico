#pragma once

#include "SDL.h"

#include "image.h"

class renderer
{

    bool finished_ = false;
    image img_;
    
public:

    // render_image() actualiza img_, si llego al final marca is finished_ = true;
    
    static void render_image(image& image, SDL_Renderer* renderer);
    static void render_intermedium_image(image& img, int max_x, SDL_Renderer* renderer);
};
