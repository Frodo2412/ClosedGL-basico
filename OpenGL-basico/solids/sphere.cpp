#include "sphere.h"

bool sphere::contains(const point3 point) const
{
    const auto x = (point.x - position_.x) * (point.x - position_.x);
    const auto y = (point.y - position_.y) * (point.y - position_.y);
    const auto z = (point.z - position_.z) * (point.z - position_.z);
    const auto r = radius_ * radius_;
    return x + y + z <= r;
}
