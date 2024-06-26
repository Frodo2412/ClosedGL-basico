﻿#pragma once

#include "ray.h"
#include "../raster/color.h"

class object
{
protected:
    vector3 position_;
    color color_;
    double reflectivity_, shininess_, translucency_, refractive_index_;

public:
    object(vector3 pos, color color, double reflectivity, double shininess, double translucency,
           double refractive_index): position_(pos), color_(color),
                                     reflectivity_(reflectivity),
                                     shininess_(shininess), translucency_(translucency),
                                     refractive_index_(refractive_index)
    {
    };
    virtual bool test_intersection(ray& rayo, vector3& point, vector3& normal);
    color get_color() const;
    vector3 get_position() const;
    double get_shininess() const;
    double get_reflectivity() const;
    virtual ~object();
    double get_translucency() const;
    double get_refractive_index() const;
    bool has_material() const;
    color get_specular_color() const;
};
