#pragma once
#include "volume.h"

class cube final : public volume
{
    point3 min_, max_;

public:
    explicit cube(const point3& position, const float side): volume(position), min_(-side / 2, -side / 2, -side / 2),
                                                             max_(side / 2, side / 2, side / 2)
    {
    }

    bool contains(point3 point) const override;
};
