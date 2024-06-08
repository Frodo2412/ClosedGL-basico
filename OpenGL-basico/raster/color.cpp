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

color color::operator+(const color &c) const
{
    return color(red_ + c.red_, green_ + c.green_, blue_ + c.blue_, alpha_ + c.alpha_);
}

color color::operator*(float f) const
{
    return color(red_ * f, green_ * f, blue_ * f, alpha_ * f);
}
