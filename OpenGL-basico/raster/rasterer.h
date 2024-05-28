#pragma once
#include "image.h"
#include "projection.h"
#include "circle.h"
#include "../transformations/view.h"
#include "../transformations/perspective.h"
#include "../transformations/viewport.h"
#include "../geometry/square.h"
#include "../scene/scene.h"

class rasterer
{
    color background_color_;
    scene * scene_;
    view* view_transformation_;
    perspective* perspective_transformation_;
    viewport* viewport_transformation_;

public:
    explicit rasterer(color background_color, scene * scene);
    static std::vector<point> rasterize(const line& line);
    static std::vector<point> rasterize(const circle& circle, bool fill);
    image rasterize(const projection& projection);
    std::vector<point> rasterize(const square& square, bool fill);
};
