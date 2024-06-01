#include "solid.h"

bool solid::contains(const vector3 point) const
{
    switch (operation_)
    {
    case and: return left_hs_->contains(point) && right_hs_->contains(point);
    case or: return left_hs_->contains(point) || right_hs_->contains(point);
    case not: return left_hs_->contains(point) && !right_hs_->contains(point);
    }
    return false;
}

std::vector<polygon> solid::get_faces() const
{
    return {};
}
