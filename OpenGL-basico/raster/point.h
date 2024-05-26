#pragma once

#include "../geometry/vector2.h"

struct point
{
    int x, y;

    point(int x, int y);
    vector2 to_vector2();
};
