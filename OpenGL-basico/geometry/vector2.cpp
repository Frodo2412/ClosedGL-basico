#include "vector2.h"

vector2::vector2(const float x, const float y)
{
    this->x = x;
    this->y = y;
}

std::ostream& operator<<(std::ostream& os, const vector2& v)
{
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}
