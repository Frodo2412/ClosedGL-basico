#pragma once

#include "volume.h"

class sphere final : public volume
{
    float radius_;

    static int definition_;

public:
    explicit sphere(const vector3& position, const float radius, const color color): volume(position, color),
        radius_(radius)
    {
    }

    bool contains(vector3 point) const override;
    std::vector<line3> get_edges() const override;
};