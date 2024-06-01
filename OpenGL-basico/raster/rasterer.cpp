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
        auto start = ln.get_start();
        auto end = ln.get_end();
        if (x >= std::min(start.x, end.x) && x <= std::max(start.x, end.x))
        {
            intersections.emplace_back(x, y0);
        }
    }

    return intersections;
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
            points.emplace_back(static_cast<int>(line.get_start().x), y, line.get_start().get_z());
        return points;
    }

    if (line.get_dy() == 0.0f) // horizontal line
    {
        if (line.get_start().x > line.get_end().x)
            return rasterize(::line(line.get_end(), line.get_start()));
        auto points = std::vector<point>();
        std::cout << "Horizontal line\n";
        for (int x = static_cast<int>(line.get_start().x); x <= static_cast<int>(line.get_end().x); x++)
            points.emplace_back(x, static_cast<int>(line.get_start().y), line.get_start().get_z());
        return points;
    }

    if (line.get_start().x > line.get_end().x)
        return rasterize(::line(line.get_end(), line.get_start()));
    std::cout << "Diagonal line\n";
    return mid_point_algorithm::raster(line);
}

// std::vector<point> rasterer::rasterize(const circle& circle, bool fill)
// {
//     std::vector<point> points;
//
//     const float x0 = circle.center.get_x();
//     const float y0 = circle.center.get_y();
//     const float radius = circle.radius;
//     float x = radius;
//     float y = 0;
//     float d = 1 - radius;
//     points.emplace_back(x0 + x, y0 + y);
//     points.emplace_back(x0 - x, y0 + y);
//     points.emplace_back(x0 + x, y0 - y);
//     points.emplace_back(x0 - x, y0 - y);
//     points.emplace_back(x0 + y, y0 + x);
//     points.emplace_back(x0 - y, y0 + x);
//     points.emplace_back(x0 + y, y0 - x);
//     points.emplace_back(x0 - y, y0 - x);
//
//     for (y = 0; y <= x; y++)
//     {
//         if (d <= 0) d += 2 * y + 1;
//         else
//         {
//             x--;
//             d += 2 * y - 2 * x + 1;
//         }
//
//         points.emplace_back(x0 + x, y0 + y);
//         points.emplace_back(x0 - x, y0 + y);
//         points.emplace_back(x0 + x, y0 - y);
//         points.emplace_back(x0 - x, y0 - y);
//
//         if (x != y)
//         {
//             points.emplace_back(x0 + y, y0 + x);
//             points.emplace_back(x0 - y, y0 + x);
//             points.emplace_back(x0 + y, y0 - x);
//             points.emplace_back(x0 - y, y0 - x);
//         }
//     }
//     if (fill)
//     {
//         x = 0;
//         y = radius;
//         d = 3 - 2 * radius;
//         while (x <= y)
//         {
//             for (int i = x0 - x; i <= x0 + x; i++)
//             {
//                 points.emplace_back(i, y0 + y);
//                 points.emplace_back(i, y0 - y);
//             }
//             for (int i = x0 - y; i <= x0 + y; i++)
//             {
//                 points.emplace_back(i, y0 + x);
//                 points.emplace_back(i, y0 - x);
//             }
//             if (d < 0)
//             {
//                 d += 4 * x + 6;
//             }
//             else
//             {
//                 d += 4 * (x - y) + 10;
//                 y--;
//             }
//             x++;
//         }
//     }
//     return points;
// }

// std::vector<point> rasterer::rasterize(const square& square, bool fill, view* view_transformation, perspective* perspective_transformation, viewport* viewport_transformation)
// {
//     std::vector<point> points;
//     vector4 a = vector4(square.get_a().get_x(), square.get_a().get_y(), square.get_a().get_z(), 1);
//     vector4 b = vector4(square.get_b().get_x(), square.get_b().get_y(), square.get_b().get_z(), 1);
//     vector4 c = vector4(square.get_c().get_x(), square.get_c().get_y(), square.get_c().get_z(), 1);
//     vector4 d = vector4(square.get_d().get_x(), square.get_d().get_y(), square.get_d().get_z(), 1);
//     a = view_transformation->transform(a);
//     b = view_transformation->transform(b);
//     c = view_transformation->transform(c);
//     d = view_transformation->transform(d);
//     a = perspective_transformation->transform(a);
//     b = perspective_transformation->transform(b);
//     c = perspective_transformation->transform(c);
//     d = perspective_transformation->transform(d);
//
//     point a_final = point(square.get_a().get_x(), square.get_a().get_y());
//     point b_final = point(square.get_b().get_x(), square.get_b().get_y());
//     point c_final = point(square.get_c().get_x(), square.get_c().get_y());
//     point d_final = point(square.get_d().get_x(), square.get_d().get_y());
//
//     line* ab = new line(a_final.to_vector2(), b_final.to_vector2());
//     line* cb = new line(c_final.to_vector2(), b_final.to_vector2());
//     line* dc = new line(d_final.to_vector2(), c_final.to_vector2());
//     line* da = new line(d_final.to_vector2(), a_final.to_vector2());
//
//     std::vector<point> points_ab = rasterize(*ab);
//     std::vector<point> points_bc = rasterize(*cb);
//     std::vector<point> points_cd = rasterize(*dc);
//     std::vector<point> points_da = rasterize(*da);
//     points.insert(points.end(), points_ab.begin(), points_ab.end());
//     points.insert(points.end(), points_bc.begin(), points_bc.end());
//     points.insert(points.end(), points_cd.begin(), points_cd.end());
//     points.insert(points.end(), points_da.begin(), points_da.end());
//     
//     return points;
// }
