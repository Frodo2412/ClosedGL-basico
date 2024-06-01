#include "raster_pipeline.h"

#include <iostream>

#include "../raster/rasterer.h"

image raster_pipeline::rasterize(const projection& projection) const
{
    std::vector<std::vector<color>> colors;

    std::vector<std::vector<float>> z_buffer;

    for (int i = 0; i < width_; i++)
    {
        std::vector<color> colors_row;
        std::vector<float> z_buffer_row;
        for (int j = 0; j < height_; j++)
        {
            colors_row.emplace_back(0, 0, 0);
            z_buffer_row.push_back(0);
        }
        colors.push_back(colors_row);
        z_buffer.push_back(z_buffer_row);
    }

    for (const auto& polygon : projection.shapes)
    {
        std::vector<pixel> polygon_pixels;
        for (auto line : polygon.edges)
        {
            const std::vector<point> points = rasterer::rasterize(line);
            for (point point : points)
            {
                polygon_pixels.emplace_back(point, polygon.fill_color);
            }
        }

        for (auto pixel : polygon_pixels)
        {
            auto pz = pixel.point.z_buffer;
            if (pz >= z_buffer[pixel.point.x][pixel.point.y])
            {
                z_buffer[pixel.point.x][pixel.point.y] = pz;
                colors[pixel.point.x][pixel.point.y] = pixel.color;
            }
        }
    }

    std::vector<pixel> pixels;

    for (int i = 0; i < width_; i++)
    {
        for (int j = 0; j < height_; j++)
        {
            pixels.emplace_back(point(i, j, 0), colors[i][j]);
        }
    }


    return image(width_, height_, pixels);
}
