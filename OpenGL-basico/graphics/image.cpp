#include "image.h"

image::image(const int width, const int height, std::vector<pixel>& vector, image_type type): width(width), height(height),
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

pixel image::get_pixel(int x, int y)
{
    if (x >= 0 && x < width && y >= 0 && y < height)
    {
        return pixels[x * (height) + y];
    }
}

image image::create_empty_image(int width, int height, image_type type)
{
    std::vector<pixel> empty_pixels; // Vector vacío
    return image(width, height, empty_pixels, type);
}
