#pragma once

#include "ray.h"
#include "../raster/color.h"

class object
{
    vector3 position_;
    color color_;
    
public:
    object(vector3 pos, color color): position_(pos), color_(color)
    {
        
    };
    virtual bool test_intersection(ray &rayo, vector3 &point, vector3 &normal, color &color);
    bool close_enough(float f1, float f2);
    color get_color();
    vector3 get_position();
    virtual ~object();
};

