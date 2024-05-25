#pragma once
#include "../geometry/vector3.h"

class camera
{
    vector3 position_, look_at_, up_;
    float fov_; // in radians
public:
    explicit camera(const vector3& position, const vector3& direction, const vector3& up, const float fov)
        : position_(position), look_at_(direction), up_(up), fov_(fov)
    {
    }

    float get_fov() const;
    vector3 get_position() const;
    vector3 get_direction() const;
};
