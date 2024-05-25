#include "scene.h"

RGBQUAD scene::get_background_color()
{
    RGBQUAD rgb;
    rgb.rgbRed = 0;
    rgb.rgbGreen = 255;
    rgb.rgbBlue = 0;
    return rgb;
}

square scene::get_square() const
{
    return square_;
}

cube scene::get_cube() const
{
    return walls_;
}

camera scene::get_camera() const
{
    return camera_;
}
