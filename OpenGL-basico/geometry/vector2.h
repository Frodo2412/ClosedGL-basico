#pragma once
#include <ostream>

struct vector2
{
    float x, y;

    vector2(float x, float y);

    friend std::ostream& operator<<(std::ostream& os, const vector2& v);
};
