#include "line.h"

vector3 line::get_start() const
{
    return start_;
}

vector3 line::get_end() const
{
    return end_;
}

vector3 line::get_direction() const
{
    return end_ - start_;
}

bool line::is_in_path(const vector3& point) const
{
    const auto direction = get_direction();
    // Vector from the line's point to the given point
    const vector3 line_to_point = point - start_;

    // Cross product of the direction vector and lineToPoint
    const vector3 cross_product = direction * line_to_point;

    // If the cross product is zero, the point is on the line
    return cross_product == vector3::zero();
}
