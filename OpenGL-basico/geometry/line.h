#pragma once
#include "vector3.h"

class line
{
    vector3 start_, end_;

public:
    explicit line(const vector3& start, const vector3& end): start_(start), end_(end)
    {
    }

    vector3 get_start() const;
    vector3 get_end() const;
    vector3 get_direction() const;

    bool is_in_path(const vector3& point) const;
};
