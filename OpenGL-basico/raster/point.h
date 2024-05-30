#pragma once

#include "../geometry/vector2.h"

struct point
{
    int x, y;
    vector2 to_vector2();
    point(int x, int y);
};
