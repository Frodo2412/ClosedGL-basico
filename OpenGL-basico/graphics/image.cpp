#include "image.h"

image::image(const int width, const int height, std::vector<pixel>& vector, image_type type): width(width),
    height(height),
    type_(type), pixels(vector)
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
