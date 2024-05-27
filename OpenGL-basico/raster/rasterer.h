#pragma once
#include "image.h"
#include "projection.h"
#include "circle.h"
#include "../transformations/view.h"
#include "../transformations/perspective.h"
#include "../transformations/viewport.h"
#include "../geometry/square.h"

class rasterer
{
    color background_color_;

public:
    explicit rasterer(color background_color);
    static std::vector<point> rasterize(const line& line);
    static std::vector<point> rasterize(const circle& circle, bool fill);
    image rasterize(const projection& projection);
    static std::vector<point> rasterize(const square& square, bool fill, view* view_transformation, perspective* perspective_transformation, viewport* viewport_transformation);
};
