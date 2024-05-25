#pragma once

#include "../geometry/vector2.h"
#include "../geometry/vector3.h"

struct vertex
{
    vector3 position, normal;
    vector2 tex_coords;

    explicit vertex(const vector3& position, const vector3& normal, const vector2 tex_coords)
        : position(position), normal(normal), tex_coords(tex_coords)
    {
    }
};
