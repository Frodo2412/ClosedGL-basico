#pragma once
#include "image.h"
#include "projection.h"

class raster_pipeline
{
    int width_, height_;

public:
    explicit raster_pipeline(const int width, const int height): width_(width), height_(height)
    {
    }

    image rasterize(const projection& projection) const;
};
