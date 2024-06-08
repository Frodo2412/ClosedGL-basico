#include "object.h"

object::~object()
{

}

bool object::test_intersection(ray &rayo, vector3 &point, vector3 &normal)
{
    return false;
}

color object::get_color()
{
    return color_;
}

vector3 object::get_position()
{
    return position_;
}

double object::get_shininess()
{
    return shininess_;
}

double object::get_reflectivity()
{
    return reflectivity_;
}

