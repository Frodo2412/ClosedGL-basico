#include "square.h"

const vector3& square::get_a() const
{
    return a_;
}

const vector3& square::get_b() const
{
    return b_;
}

const vector3& square::get_c() const
{
    return c_;
}

const vector3& square::get_d() const
{
    return d_;
}

bool square::contains(int i, int y) const
{
    return a_.get_x() <= i && i <= b_.get_x() && a_.get_y() <= y && y <= c_.get_y();
}

RGBQUAD square::get_color()
{
    RGBQUAD rgb;
    rgb.rgbRed = 255;
    rgb.rgbGreen = 0;
    rgb.rgbBlue = 0;
    return rgb;
}
