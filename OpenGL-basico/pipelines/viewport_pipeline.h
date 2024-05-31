#pragma once

#include "projection.h"
#include "../geometry/vector2.h"
#include "../transformations/viewport.h"

class viewport_pipeline
{
    viewport viewport_;

public:
    explicit viewport_pipeline(int width, int height, vector2 origin) : viewport_(viewport(width, height, origin))
    {
    }

    projection get_viewport_coordinates(const projection& ndc_projection) const;
};
