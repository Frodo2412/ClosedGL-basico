#pragma once

#include "object.h"

class sphere : public object
{
	float radius_;
public:
    sphere(vector3 pos, float radius, color color) : object(pos, color), radius_(radius)
    {
    }
	
    virtual bool test_intersection(ray &rayo, vector3 &point, vector3 &normal, color &color) override;
	float get_radius() const;
	~sphere() override;
};
