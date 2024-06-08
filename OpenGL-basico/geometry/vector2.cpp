#include "vector2.h"

vector2::vector2(const double x, const double y)
{
    this->x = x;
    this->y = y;
}

std::ostream& operator<<(std::ostream& os, const vector2& v)
{
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}

double vector2::get_x() const
{
    return x;
}

double vector2::get_y() const
{
    return y;
}
