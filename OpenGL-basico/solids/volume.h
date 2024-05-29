#pragma once

#include "point3.h"

class volume
{
protected:
    point3 position_;

    explicit volume(const point3& position): position_(position)
    {
    }

public:
    virtual ~volume() = default;

    virtual bool contains(point3 point) const = 0;
};
