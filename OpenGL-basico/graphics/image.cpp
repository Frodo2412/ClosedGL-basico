#include "image.h"
#include <SDL.h>

image::image(const int width, const int height, std::vector<pixel>& vector, image_type type): width(width),
    height(height),
    pixels(vector), type_(type)
{
}

std::string image::get_type()
{
    switch (type_)
    {
    case normal:
        return "normal";
    case reflectividad:
        return "reflectividad";
    case refractividad:
        return "refractividad";
    }
}

int image::get_width()
{
    return width;
}

int image::get_height()
{
    return height;
}

pixel image::get_pixel(int x, int y)
{
    return pixels[y * width + x];
}

std::vector<Uint32> image::get_pixel_data()
{
    std::vector<Uint32> pixel_data(width * height);
    for (const auto& px : pixels)
    {
        int x = px.x_;
        int y = px.y_;
        const color& col = px.color_;
        Uint32 pixel_color = SDL_MapRGBA(SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888), col.get_red(), col.get_green(),
                                 col.get_blue(), 255);
        pixel_data[y * width + x] = pixel_color;
    }
    return pixel_data;
}
