#include "cube.h"

bool cube::contains(const point3 point) const
{
    const auto min_x = position_.x - min_.x;
    const auto max_x = position_.x + max_.x;
    const auto is_x = point.x >= min_x && point.x <= max_x;

    const auto min_y = position_.y - min_.y;
    const auto max_y = position_.y + max_.y;
    const auto is_y = point.y >= min_y && point.y <= max_y;

    const auto min_z = position_.z - min_.z;
    const auto max_z = position_.z + max_.z;
    const auto is_z = point.z >= min_z && point.z <= max_z;

    return is_x && is_y && is_z;
}
