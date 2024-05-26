#include "point.h"

point::point(const int x, const int y)
{
    this->x = x;
    this->y = y;
}

vector2 point::to_vector2()
{
    return vector2(this->x, this->y);
}
