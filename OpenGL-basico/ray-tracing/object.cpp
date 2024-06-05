#include "object.h"

#define EPSILON 1e-21f;

object::~object()
{

}

bool object::test_intersection(ray &rayo, vector3 &point, vector3 &normal, color &color)
{
    return false;
}

bool object::close_enough(float f1, float f2)
{
    return fabs(f1-f2) < EPSILON;
}

color object::get_color()
{
    return color_;
}

vector3 object::get_position()
{
    return position_;
}

int object::get_id()
{
    return id_;
}

