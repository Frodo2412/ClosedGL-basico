#include "sphere.h"

int sphere::definition_ = 20;

bool sphere::contains(const vector3 point) const
{
    const auto x = (point.x - position_.x) * (point.x - position_.x);
    const auto y = (point.y - position_.y) * (point.y - position_.y);
    const auto z = (point.z - position_.z) * (point.z - position_.z);
    const auto r = radius_ * radius_;
    return x + y + z <= r;
}

std::vector<line> sphere::get_edges() const
{
    return {};
}

// std::vector<vector3> sphere::get_vertexes() const
// {
//     std::vector<vector3> vertexes;
//
//     for (int i = 0; i < definition_; i++)
//     {
//         const auto theta = 2 * 3.14 * i / definition_;
//         for (int j = 0; j < definition_; j++)
//         {
//             const auto phi = 3.14 * j / definition_;
//             const auto x = position_.x + radius_ * sin(phi) * cos(theta);
//             const auto y = position_.y + radius_ * sin(phi) * sin(theta);
//             const auto z = position_.z + radius_ * cos(phi);
//             vertexes.emplace_back(x, y, z);
//         }
//     }
//
//     return vertexes;
// }
