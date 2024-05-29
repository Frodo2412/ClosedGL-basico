#pragma once

#include "volume.h"

class sphere final : public volume
{
    float radius_;

public:
    explicit sphere(const point3& position, const float radius): volume(position), radius_(radius)
    {
    }

    bool contains(point3 point) const override;
};
