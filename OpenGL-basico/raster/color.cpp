#include "color.h"

RGBQUAD color::to_rgb() const
{
    RGBQUAD rgba;
    rgba.rgbRed = red_;
    rgba.rgbGreen = green_;
    rgba.rgbBlue = blue_;
    return rgba;
}

void color::set_alpha(float alpha)
{
    alpha_ = alpha;
}

float color::get_alpha() const
{
    return alpha_;
}
