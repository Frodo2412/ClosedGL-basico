#pragma once

class vector2
{
    float x_, y_;

public:
    vector2() : x_(0.0), y_(0.0)
    {
    }

    explicit vector2(const float x, const float y) : x_(x), y_(y)
    {
    }

    float get_x() const;
    float get_y() const;
};
