#pragma once

#include "volume.h"

class sphere final : public volume
{
    float radius_;

    static int definition_;

public:
    explicit sphere(const point3& position, const float radius, const color color): volume(position, color), radius_(radius)
    {
    }

    bool contains(point3 point) const override;
    std::vector<point3> get_vertexes() const override;
};
