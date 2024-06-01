#pragma once

#include <vector>

#include "../geometry/vector3.h"
#include "../raster/color.h"
#include "../raster/line.h"
#include "../raster/polygon.h"

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
    virtual std::vector<polygon> get_faces() const = 0;
};
