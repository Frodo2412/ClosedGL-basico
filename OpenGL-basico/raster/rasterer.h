#pragma once

#include <vector>

#include "circle.h"
#include "line.h"
#include "../transformations/view.h"
#include "../transformations/perspective.h"
#include "../transformations/viewport.h"
#include "../geometry/square.h"

class rasterer
{
public:
    static std::vector<point> rasterize(const line& line);
    static std::vector<point> rasterize(const circle& circle, bool fill);
    // static std::vector<point> rasterize(const square& square, bool fill, view* view_transformation,
                                        // perspective* perspective_transformation,viewport* viewport_transformation);
};
