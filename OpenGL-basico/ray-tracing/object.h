#pragma once

#include "ray.h"
#include "../raster/color.h"

class object
{
    vector3 position_;
    color color_;
    double reflectivity_;
    double shininess_;
    
public:
    object(vector3 pos, color color, double reflectivity, double shininess): position_(pos), color_(color), reflectivity_(reflectivity), shininess_(shininess)
    {
    };
    virtual bool test_intersection(ray &rayo, vector3 &point, vector3 &normal);
    color get_color();
    vector3 get_position();
    double get_shininess();
    double get_reflectivity();
    virtual ~object();
};

