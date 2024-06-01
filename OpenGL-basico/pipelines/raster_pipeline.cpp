#include "raster_pipeline.h"
#include <algorithm>
#include <iostream>
#include "scene.h"
#include "../raster/rasterer.h"

std::vector<vector3> find_intersections(float y0, const std::vector<line>& lines)
{
    std::vector<vector3> intersections;

    for (const auto& ln : lines)
    {
        if (static_cast<int>(ln.get_dx()) == 0) { continue; }
        if (static_cast<int>(ln.get_dy()) == 0) { continue; }

        float x = (y0 - ln.get_y_intercept()) / ln.get_dy() * ln.get_dx();

        auto start = ln.get_start();
        auto end = ln.get_end();
        if (x >= std::min(start.x, end.x) && x <= std::max(start.x, end.x))
        {
            intersections.emplace_back(x, y0, ln.get_z(x, y0));
        }
    }

    return intersections;
}

image raster_pipeline::rasterize(const projection& projection) const
{
    std::cout << "Rasterizing projection\n";

    const auto polygons = projection.shapes;

    std::cout << "- Number of polygons: " << polygons.size() << "\n";

    try
    {
        std::vector<std::vector<color>> colors(width_, std::vector<color>(height_));
        std::vector<std::vector<float>> z_buffer(width_, std::vector<float>(height_));

        std::cout << "- Created matrices for rasterization: " << width_ << "x" << height_ << "\n";

        for (int i = 0; i < width_; i++)
        {
            for (int j = 0; j < height_; j++)
            {
                colors[i][j] = color(0, 0, 0);
                z_buffer[i][j] = std::numeric_limits<float>::infinity();
            }
        }

        for (const auto& polygon : projection.shapes)
        {
            std::vector<pixel> polygon_pixels;
            for (auto line : polygon.edges)
            {
                const std::vector<point> points = rasterer::rasterize(line);
                for (const auto& pt : points)
                {
                    polygon_pixels.emplace_back(pt, polygon.fill_color);
                }
            }

            for (int y = 0; y < height_; y++)
            {
                auto intersections = find_intersections(static_cast<float>(y), polygon.edges);

                if (intersections.empty()) { continue; }

                std::sort(intersections.begin(), intersections.end(), [](const vector3& a, const vector3& b)
                {
                    return a.x < b.x;
                });

                bool inside = intersections[0].x < 0;
                int intersection_index = 0;

                for (int x = 0; x < width_; x++)
                {
                    if (x >= intersections[intersection_index].x)
                    {
                        if (intersections.size() == intersection_index + 1) { break; }
                        inside = !inside;
                        intersection_index++;
                    }


                    if (inside)
                    {
                        const float z = intersections[intersection_index - 1].z;
                        // Use the z value from the last intersection
                        polygon_pixels.emplace_back(point(x, y, z), polygon.fill_color);
                    }
                }
            }

            for (const auto& pixel : polygon_pixels)
            {
                const auto pz = pixel.point.z_buffer;
                if (pz < z_buffer[pixel.point.x][pixel.point.y])
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
    catch (const std::exception& e)
    {
        std::cerr << e.what() << "\n";
        throw;
    }
}
