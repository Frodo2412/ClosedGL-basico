#include "camera.h"

float camera::get_fov() const
{
    return fov_;
}

vector3 camera::get_position() const
{
    return position_;
}

vector3 camera::get_forward() const
{
    return look_at_ - position_;
}

vector3 camera::get_up() const
{
    return up_;
}

vector3 camera::get_direction() const
{
    return look_at_ - position_;
}

vector3 camera::get_right() const
{
    vector3 right = get_forward() * get_up();
    return right;
}

float camera::get_near() const
{
    return near_;
}

float camera::get_far() const
{
    return far_;
}
