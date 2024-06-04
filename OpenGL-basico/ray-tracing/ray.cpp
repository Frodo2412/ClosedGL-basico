#include "ray.h"

vector3 ray::get_origin() const
{
    return origin_;
}

vector3 ray::get_direction() const
{
    return direction_;
}

vector3 ray::get_ray_vector() const
{
    return direction_ - origin_;
}

void ray::set_origin(vector3 origin)
{
    origin_ = origin;
}

void ray::set_direction(vector3 dir)
{
    direction_ = dir;
}

