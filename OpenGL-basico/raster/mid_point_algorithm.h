#pragma once
#include <vector>

#include "circle.h"
#include "line.h"
#include "pixel.h"
#include "../geometry/square.h"
#include "../transformations/view.h"
#include "../transformations/perspective.h"
#include "../transformations/viewport.h"

class mid_point_algorithm
{
public:
    static std::vector<point> raster(const line& line);
    static std::vector<point> raster(const circle& circle, bool fill);
    static std::vector<point> raster(const square& square, bool fill, view* view_transformation, perspective* perspective_transformation, viewport* viewport_transformation);
};
