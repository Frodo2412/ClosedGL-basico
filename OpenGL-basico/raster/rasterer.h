#pragma once
#include "image.h"
#include "projection.h"

class rasterer
{
    color background_color_;

public:
    explicit rasterer(color background_color);

    static std::vector<point> rasterize(const line& line);
    image rasterize(const projection& projection);
};
