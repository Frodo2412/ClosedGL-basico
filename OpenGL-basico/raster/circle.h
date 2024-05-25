#pragma once
#include "../geometry/vector2.h"

struct circle
{
    // (x - center.x)^2 + (y - center.y)^2 = r^2 -> y = sqrt(r^2 - (x - center.x)^2) + center.y
    vector2 center;
    float radius;

    explicit circle(vector2 center, float radius);

    float get_y(int x) const;
};
