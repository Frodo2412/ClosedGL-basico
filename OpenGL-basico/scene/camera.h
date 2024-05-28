#pragma once
#include "../geometry/vector3.h"

class camera
{
    vector3 position_, look_at_, up_;
    float fov_; // in radians
    float near_;
    float far_;
public:
    explicit camera(const vector3& position, const vector3& direction, const vector3& up, const float fov, float near, float far)
        : position_(position), look_at_(direction), up_(up), fov_(fov), near_(near), far_(far)
    {
    }

    float get_fov() const;
    vector3 get_position() const;
    vector3 get_direction() const;
    vector3 get_forward() const;
    vector3 get_up() const;
    vector3 get_right() const;
    float get_near() const;
    float get_far() const;
};
