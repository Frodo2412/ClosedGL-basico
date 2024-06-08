#pragma once
#include "object.h"

class cylinder : public object
{
    float radius_;
    float height_;
    vector3 axis_;
public:
    cylinder(vector3 pos, float radius, float height, vector3 axis, color color, float reflectivity, float shininess) : object(pos, color, reflectivity, shininess), radius_(radius), height_(height), axis_(axis.normalize())
    {
    }

    bool test_intersection(ray &rayo, vector3 &point, vector3 &normal) override;
};