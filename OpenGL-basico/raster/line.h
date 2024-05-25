#pragma once
#include "../geometry/vector2.h"

class line
{
    // y = mx + n
    vector2 start_, end_;
    float m_, n_;

public:
    explicit line(vector2 start, vector2 end);

    float get_y(int x) const;
    vector2 get_start() const;
    vector2 get_end() const;
    float get_dx() const;

    float get_dy() const;
    float get_y_intercept() const;
};
