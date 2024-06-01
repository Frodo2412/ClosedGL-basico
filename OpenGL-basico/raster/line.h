#pragma once
#include "../geometry/vector3.h"

class line
{
    // y = mx + n
    vector3 start_, end_;
    float m_, n_;

public:
    explicit line(vector3 start, vector3 end);

    float get_y(int x) const;
    vector3 get_start() const;
    vector3 get_end() const;
    float get_dx() const;

    float get_dy() const;
    float get_y_intercept() const;

    float get_z(int x, int y) const;
};
