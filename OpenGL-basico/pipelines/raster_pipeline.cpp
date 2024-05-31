#include "raster_pipeline.h"

#include <iostream>

#include "../raster/rasterer.h"

image raster_pipeline::rasterize(const projection& projection) const
{
    std::vector<pixel> pixels(width_ * height_);

    for (const auto& polygon : projection.shapes)
    {
        for (auto line : polygon.edges)
        {
            const std::vector<point> points = rasterer::rasterize(line);
            for (point point : points)
            {
                pixels.emplace_back(point, polygon.fill_color);
            }
        }
    }

    return image(width_, height_, pixels);
}
