#pragma once
#include "object.h"

class cylinder : public object
{
    double radius_;
    double height_;

public:
    cylinder(vector3 pos, double radius, double height, vector3, color color, double reflectivity,
             double shininess, double translucency,
             double refractive_index) : object(pos, color, reflectivity, shininess, translucency, refractive_index),
                                        radius_(radius), height_(height)
    {
    }

    bool test_intersection(ray& rayo, vector3& point, vector3& normal) override;
};
