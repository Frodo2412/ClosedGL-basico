#include "line.h"

line::line(const vector2 start, const vector2 end): start_(start), end_(end)
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

vector2 line::get_start() const
{
    return start_;
}

vector2 line::get_end() const
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
