#include "vector2.h"

vector2::vector2(const float x, const float y)
{
    this->x = x;
    this->y = y;
}

float vector2::get_x() const
{
    return x;
}

float vector2::get_y() const
{
    return y;
}
