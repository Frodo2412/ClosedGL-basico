#pragma once

#include "../geometry/vector3.h"

class ray
{
    vector3 origin_, direction_;

public:
    ray()
    {
        origin_ = {0, 0, 0};
        direction_ = {0, 0, 0};
    }

    ray(vector3 origin, vector3 direction) : origin_(origin), direction_(direction)
    {
    }

    vector3 get_origin() const;
    vector3 get_direction() const;
    vector3 get_ray_vector() const;

    void set_origin(vector3 origin);
    void set_direction(vector3 dir);
    ray refract(const vector3& vector3, const ::vector3& intersection_normal, double get_refractive_index) const;
};
