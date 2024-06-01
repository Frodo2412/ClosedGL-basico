#pragma once

#include "../geometry/vector2.h"

struct point
{
    int x, y;
    float z_buffer;
    vector2 to_vector2() const;
    explicit point(int x, int y, float z_buffer);
};
