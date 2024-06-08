#pragma once

#include "ray.h"
#include "../raster/color.h"

class object
{
    vector3 position_;
    color color_;
    float reflectivity_;
    float shininess_;
    
public:
    object(vector3 pos, color color, float reflectivity, float shininess): position_(pos), color_(color), reflectivity_(reflectivity), shininess_(shininess)
    {
    };
    virtual bool test_intersection(ray &rayo, vector3 &point, vector3 &normal);
    bool close_enough(float f1, float f2);
    color get_color();
    vector3 get_position();
    float get_shininess();
    float get_reflectivity();
    virtual ~object();
};

