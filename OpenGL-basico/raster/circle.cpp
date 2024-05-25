#include "circle.h"

#include <cmath>

circle::circle(vector2 center, float radius): center(center), radius(radius)
{
}

float circle::get_y(const int x) const
{
    const auto xf = static_cast<float>(x);
    return sqrt(radius * radius - (xf - center.x) * (xf - center.x)) + center.y;
}
