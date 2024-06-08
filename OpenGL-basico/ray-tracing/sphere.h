#pragma once

#include "object.h"

class sphere : public object
{
	float radius_;
public:
    sphere(vector3 pos, float radius, color color, float reflectivity, float shininess) : object(pos, color, reflectivity, shininess), radius_(radius)
    {
    }
	
    bool test_intersection(ray &rayo, vector3 &point, vector3 &normal) override;
	float get_radius() const;
	~sphere() override;
};
