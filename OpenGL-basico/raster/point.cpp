#include "point.h"


vector2 point::to_vector2() const
{
    return vector2(this->x, this->y);
}

point::point(int x, int y, float z_buffer)
{
    this->x = x;
    this->y = y;
    this->z_buffer = z_buffer;
}
