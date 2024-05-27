#include "rasterer.h"

#include <algorithm>
#include <iostream>

#include "mid_point_algorithm.h"

std::vector<vector2> find_intersections(float y0, const std::vector<line>& lines)
{
    std::vector<vector2> intersections;

    for (const auto& ln : lines)
    {
        // Check if the line is vertical to avoid division by zero
        if (ln.get_dx() == 0)
        {
            continue;
        }

        // Calculate the x-coordinate of the intersection
        float x = (y0 - ln.get_y_intercept()) / ln.get_dy() * ln.get_dx();

        // Check if the intersection point is within the segment
        vector2 start = ln.get_start();
        vector2 end = ln.get_end();
        if (x >= std::min(start.x, end.x) && x <= std::max(start.x, end.x))
        {
            intersections.emplace_back(x, y0);
        }
    }

    return intersections;
}

rasterer::rasterer(const color background_color): background_color_(background_color)
{
}

std::vector<point> rasterer::rasterize(const line& line)
{
    std::cout << "Drawing line from " << line.get_start() << " to " << line.get_end() << "\n";
    if (line.get_dx() == 0.0f) // vertical line
    {
        if (line.get_start().y > line.get_end().y)
            return rasterize(::line(line.get_end(), line.get_start()));
        auto points = std::vector<point>();
        std::cout << "Vertical line\n";
        for (int y = static_cast<int>(line.get_start().y); y <= static_cast<int>(line.get_end().y); y++)
            points.emplace_back(static_cast<int>(line.get_start().x), y);
        return points;
    }
    
    if (line.get_dy() == 0.0f) // horizontal line
    {
        if (line.get_start().x > line.get_end().x)
            return rasterize(::line(line.get_end(), line.get_start()));
        auto points = std::vector<point>();
        std::cout << "Horizontal line\n";
        for (int x = static_cast<int>(line.get_start().x); x <= static_cast<int>(line.get_end().x); x++)
            points.emplace_back(x, static_cast<int>(line.get_start().y));
        return points;
    }
    
    if (line.get_start().x > line.get_end().x)
        return rasterize(::line(line.get_end(), line.get_start()));
    std::cout << "Diagonal line\n";
    return mid_point_algorithm::raster(line);
}

image rasterer::rasterize(const projection& projection)
{
    std::vector<pixel> pixels;
    for (const auto& shape : projection.shapes)
    {
        const auto lines = shape.get_lines();
        for (auto line : lines)
        {
            const auto points = mid_point_algorithm::raster(line);
            for (auto point : points)
            {
                pixels.emplace_back(point, shape.fill_color);
            }
        }

        for (int y = 0; y < projection.height; y++)
        {
            auto intersections = find_intersections(static_cast<float>(y), lines);
            std::sort(intersections.begin(), intersections.end(), [](const vector2& a, const vector2& b)
            {
                return a.x < b.x;
            });

            auto next_intersection_index = 0;
            auto inside = intersections[0].x < 0;

            for (int x = 0; x < projection.width; x++)
            {
                if (static_cast<float>(x) > intersections[next_intersection_index].x)
                {
                    inside = !inside;
                    next_intersection_index++;
                }
                if (inside)
                {
                    pixels.emplace_back(point(x, y), shape.fill_color);
                }
                else
                {
                    pixels.emplace_back(point(x, y), background_color_);
                }
            }
        }
    }
    return image(projection.width, projection.height, pixels);
}
