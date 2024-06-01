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

float line::get_z(int x, int y) const
{
    float tx, ty;

    // Calculate tx and ty
    if (end_.x != start_.x) {
        tx = (x - start_.x) / (end_.x - start_.x);
    } else if (x != start_.x) {
        throw std::invalid_argument("Given x is not on the line");
    } else {
        tx = 0; // x is start_.x since start_.x == end_.x
    }

    if (end_.y != start_.y) {
        ty = (y - start_.y) / (end_.y - start_.y);
    } else if (y != start_.y) {
        throw std::invalid_argument("Given y is not on the line");
    } else {
        ty = 0; // y is start_.y since start_.y == end_.y
    }

    // Ensure tx and ty are approximately equal
    if (std::abs(tx - ty) > 1e-6) {
        throw std::invalid_argument("Given (x, y) pair is not on the line");
    }

    // Calculate the corresponding z using tx (or ty, since they should be equal)
    float tz = tx; // or ty
    float z = start_.z + tz * (end_.z - start_.z);

    return z;
}
