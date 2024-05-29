#include "solid.h"

bool solid::contains(const point3 point) const
{
    switch (operation_)
    {
    case and: return left_hs_->contains(point) && right_hs_->contains(point);
    case or: return left_hs_->contains(point) || right_hs_->contains(point);
    case not: return left_hs_->contains(point) && !right_hs_->contains(point);
    }
    return false;
}
