#include "color.h"

RGBQUAD color::to_rgb() const
{
    RGBQUAD rgba;
    rgba.rgbRed = red_;
    rgba.rgbGreen = green_;
    rgba.rgbBlue = blue_;
    return rgba;
}

void color::set_alpha(double alpha)
{
    alpha_ = alpha;
}

double color::get_alpha() const
{
    return alpha_;
}

color color::operator+(const color& c) const
{
    return color(red_ + c.red_, green_ + c.green_, blue_ + c.blue_, alpha_ + c.alpha_);
}

color color::operator*(double f) const
{
    return color(red_ * f, green_ * f, blue_ * f, alpha_ * f);
}

color operator*(const color& c1, const color& c2)
{
    return color(c1.get_red() * c2.get_red(), c1.get_green() * c2.get_green(), c1.get_blue() * c2.get_blue());
}

color operator*(double f, const color& c)
{
    return color(c.get_red() * f, c.get_green() * f, c.get_blue() * f, c.get_alpha() * f);
}


color color::operator/(double f) const
{
    return color(red_ / f, green_ / f, blue_ / f, alpha_ / f);
}

color color::operator+=(const color& c)
{
    red_ += c.red_;
    green_ += c.green_;
    blue_ += c.blue_;
    alpha_ += c.alpha_;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const color& c)
{
    os << "Color: (" << c.red_ << ", " << c.green_ << ", " << c.blue_ << ", " << c.alpha_ << ")";
    return os;
}
