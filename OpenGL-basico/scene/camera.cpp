#include "camera.h"

float camera::get_fov() const
{
    return fov_;
}

vector3 camera::get_position() const
{
    return position_;
}

vector3 camera::get_direction() const
{
    return look_at_ - position_;
}

vector3 camera::get_up() const
{
    return up_;
}

vector3 camera::get_near() const
{
    return vector3::zero();
}

vector3 camera::get_far() const
{
    return get_position() + get_direction().normalize() * 100000000.0f;
}
