#pragma once

#include "object.h"

class sphere : public object
{
	double radius_;
public:
    sphere(vector3 pos, double radius, color color, double reflectivity, double shininess) : object(pos, color, reflectivity, shininess), radius_(radius)
    {
    }
	
    bool test_intersection(ray &rayo, vector3 &point, vector3 &normal) override;
	double get_radius() const;
	~sphere() override;
};
