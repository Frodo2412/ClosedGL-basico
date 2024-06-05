#pragma once
#include <vector>

#include "../raster/color.h"
#include "../geometry/vector3.h"
#include "object.h"
class light
{
    vector3 position_;
    color color_;
    float intensity_;//entre 0 y 1, multiplica el r g b del color_
public:
    light(vector3 pos, color color, float intensity) : position_(pos), color_(color), intensity_(intensity)
    {
        
    }
    
    bool compute_illumination(vector3 &intersection_point, vector3 &normal, std::vector<object*> objects, object* current, color & color, float & intensity);
    vector3 get_position();
    color get_color();
    float get_intensity();
    ~light();
};
