#pragma once
#include "object.h"

class cylinder : public object
{
    double radius_;
    double height_;
    vector3 axis_;

public:
    cylinder(vector3 pos, double radius, double height, vector3 axis, color color, double reflectivity,
             double shininess, double translucency,
             double refractive_index) : object(pos, color, reflectivity, shininess, translucency, refractive_index),
                                        radius_(radius), height_(height), axis_(axis.normalize())
    {
    }

    bool test_intersection(ray& rayo, vector3& point, vector3& normal) override;
};
