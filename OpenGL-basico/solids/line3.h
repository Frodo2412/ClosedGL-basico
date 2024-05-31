#pragma once

#include "../geometry/vector3.h"

class line3
{
    vector3 start_, end_;

public:
    explicit line3(vector3 start, vector3 end);

    vector3 get_start() const;
    vector3 get_end() const;
};
