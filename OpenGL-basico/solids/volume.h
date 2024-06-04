#pragma once

#include <vector>

#include "line3.h"
#include "../geometry/vector3.h"
#include "../raster/color.h"

class volume
{
protected:
    vector3 position_;
    color color_;

    explicit volume(const vector3& position, const color color): position_(position), color_(color)
    {
    }

public:
    
    virtual ~volume() = default;

    vector3 get_position() const;
    color get_color() const;

    virtual bool contains(vector3 point) const = 0;
    virtual std::vector<line3> get_edges() const = 0;

    
};
