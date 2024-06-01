#include "line.h"

line::line(const vector3 start, const vector3 end): start_(start), end_(end)
{
    const auto dx = end.x - start.x;
    const auto dy = end.y - start.y;

    m_ = dy / dx;
    n_ = start.y - m_ * start.x;
}

float line::get_y(const int x) const
{
    return m_ * static_cast<float>(x) + n_;
}

vector3 line::get_start() const
{
    return start_;
}

vector3 line::get_end() const
{
    return end_;
}

float line::get_dx() const
{
    return end_.x - start_.x;
}

float line::get_dy() const
{
    return end_.y - start_.y;
}

float line::get_y_intercept() const
{
    return n_;
}

float line::get_z(const int x, const int y) const
{
    if (static_cast<float>(x) == start_.x &&
        static_cast<float>(y) == start_.y)
        return start_.z;


    const float tx = (x - start_.x) / (end_.x - start_.x);

    const float z = start_.z + tx * (end_.z - start_.z);

    return z;
}
