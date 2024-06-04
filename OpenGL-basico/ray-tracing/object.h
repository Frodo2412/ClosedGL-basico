#pragma once

#include "ray.h"
#include "../raster/color.h"

class object
{
    color color_;
    
public:
    object(color color): color_(color)
    {
        
    };
    virtual bool test_intersection(ray &rayo, vector3 &point, vector3 &normal, color &color);
    bool close_enough(float f1, float f2);
    color get_color();
    virtual ~object();
};

