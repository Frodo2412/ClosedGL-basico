#include "color.h"

RGBQUAD color::to_rgb() const
{
    RGBQUAD rgba;
    rgba.rgbRed = red_;
    rgba.rgbGreen = green_;
    rgba.rgbBlue = blue_;
    return rgba;
}
