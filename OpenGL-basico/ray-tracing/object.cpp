#include "object.h"

object::~object() = default;

double object::get_translucency() const
{
    return translucency_;
}

double object::get_refractive_index() const
{
    return refractive_index_;
}

bool object::test_intersection(ray& rayo, vector3& point, vector3& normal)
{
    return false;
}

color object::get_color() const
{
    return color_;
}

vector3 object::get_position() const
{
    return position_;
}

double object::get_shininess() const
{
    return shininess_;
}

double object::get_reflectivity() const
{
    return reflectivity_;
}
