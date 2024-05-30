#pragma once

#include <vector>

#include "point3.h"
#include "../raster/color.h"

class volume
{
protected:
    point3 position_;
    color color_;

    explicit volume(const point3& position, const color color): position_(position), color_(color)
    {
    }

public:
    virtual ~volume() = default;

    point3 get_position() const;
    color get_color();

    virtual bool contains(point3 point) const = 0;
    virtual std::vector<point3> get_vertexes() const = 0;
};
