#pragma once

#include "volume.h"
#include "../raster/line.h"

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
    std::vector<polygon> get_faces() const override;
};
