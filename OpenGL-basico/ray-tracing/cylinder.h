#pragma once
#include "object.h"
#include "plane.h"

class cylinder : public object
{
    double radius_;
    double height_;
    plane top_, bottom_;

public:
    cylinder(vector3 pos, double radius, double height, vector3, color color, double reflectivity,
             double shininess, double translucency,
             double refractive_index) : object(pos, color, reflectivity, shininess, translucency, refractive_index),
                                        radius_(radius), height_(height), top_(
                                            position_ + vector3(0, height_, 0), vector3(0, 1, 0), color, radius, radius,
                                            reflectivity,
                                            shininess, translucency, refractive_index),
                                        bottom_(position_, vector3(0, -1, 0), color, radius, radius, reflectivity,
                                                shininess, translucency,
                                                refractive_index)
    {
    }

    bool test_intersection(ray& rayo, vector3& point, vector3& normal) override;
};
