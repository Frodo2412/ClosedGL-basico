#include "cube.h"

bool cube::contains(const vector3 point) const
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

std::vector<line3> cube::get_edges() const
{
    const vector3 max = position_ + max_;
    const vector3 a = {min_.x + position_.x, max_.y + position_.y, max_.z + position_.z};
    const vector3 b = {min_.x + position_.x, min_.y + position_.y, max_.z + position_.z};
    const vector3 c = {max_.x + position_.x, min_.y + position_.y, max_.z + position_.z};
    const vector3 d = {min_.x + position_.x, max_.y + position_.y, min_.z + position_.z};
    const vector3 e = {max_.x + position_.x, max_.y + position_.y, min_.z + position_.z};
    const vector3 f = {max_.x + position_.x, min_.y + position_.y, min_.z + position_.z};
    const vector3 min = position_ + min_;

    return {
        // front
        line3(max, a),
        line3(max, c),
        line3(b, a),
        line3(b, c),
        // back
        line3(min, d),
        line3(min, f),
        line3(e, d),
        line3(e, f),
        // sides
        line3(a, d),
        line3(b, min),
        line3(c, f),
        line3(max, e),
    };
}
