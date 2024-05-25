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
