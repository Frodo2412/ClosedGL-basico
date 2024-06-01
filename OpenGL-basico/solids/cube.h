#pragma once
#include "volume.h"
#include "../raster/line.h"

class cube final : public volume
{
    vector3 min_, max_;

public:
    explicit cube(const vector3& position, const float side, const color color): volume(position, color),
        min_(-side / 2, -side / 2, -side / 2),
        max_(side / 2, side / 2, side / 2)
    {
    }

    bool contains(vector3 point) const override;
    std::vector<line> get_edges() const override;
};
