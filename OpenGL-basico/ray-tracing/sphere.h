#pragma once

#include "object.h"

class sphere : public object
{
public:
    sphere(color color) : object(color)
    {
    }
	
    virtual bool test_intersection(ray &rayo, vector3 &point, vector3 &normal, color &color) override;
	~sphere() override;
};
