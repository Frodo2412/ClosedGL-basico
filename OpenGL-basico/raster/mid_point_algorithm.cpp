#include "mid_point_algorithm.h"

#include <cmath>
#include <iostream>
#include <vector>


int to_int(const float x)
{
    return static_cast<int>(std::round(x));
}

std::vector<point> mid_point_upwards(const line& line)
{
    std::vector<point> points;

    const auto start = line.get_start();
    const auto end = line.get_end();

    const auto a = line.get_dy();
    const auto b = -line.get_dx();

    const int x0 = to_int(start.x);
    const auto y0 = to_int(start.y);

    points.emplace_back(x0, y0);

    int y = y0;

    auto d = a + b / 2;
    for (int x = x0; static_cast<float>(x) < end.x; x++)
    {
        if (d < 0) { d += a; }
        else
        {
            d += a + b;
            y++;
        }
        points.emplace_back(x, y);
    }

    return points;
}

std::vector<point> mid_point_downwards(const line& line)
{
    std::vector<point> points;

    const auto start = line.get_start();
    const auto end = line.get_end();

    const auto a = line.get_dy();
    const auto b = -line.get_dx();

    const int x0 = to_int(start.x);
    const auto y0 = to_int(start.y);

    points.emplace_back(x0, y0);

    int y = y0;

    auto d = a + b / 2;
    for (int x = x0; static_cast<float>(x) < end.x; x++)
    {
        if (d > 0) { d += a; }
        else
        {
            d += a + b;
            y--;
        }
        points.emplace_back(x, y);
    }

    return points;
}

std::vector<point> mid_point_algorithm::raster(const line& line)
{
    const auto start = line.get_start();
    const auto end = line.get_end();

    if (start.y <= end.y) { return mid_point_upwards(line); }
    return mid_point_downwards(line);
}

std::vector<point> mid_point_algorithm::raster(const circle& circle)
std::vector<point> mid_point_algorithm::raster(const circle& circle, bool fill)
{
    std::vector<point> points;

    const float x0 = circle.center.get_x();
    const float y0 = circle.center.get_y();
    const float radius = circle.radius;
    float x = radius;
    float y = 0;
    float d = 1 - radius;
    points.emplace_back(x0 + x, y0 + y);
    points.emplace_back(x0 - x, y0 + y);
    points.emplace_back(x0 + x, y0 - y);
    points.emplace_back(x0 - x, y0 - y);
    points.emplace_back(x0 + y, y0 + x);
    points.emplace_back(x0 - y, y0 + x);
    points.emplace_back(x0 + y, y0 - x);
    points.emplace_back(x0 - y, y0 - x);

    for (y = 0; y <= x; y++)
    {
        if (d <= 0) d += 2 * y + 1;
        else
        {
            x--;
            d += 2 * y - 2 * x + 1;
        }

        points.emplace_back(x0 + x, y0 + y);
        points.emplace_back(x0 - x, y0 + y);
        points.emplace_back(x0 + x, y0 - y);
        points.emplace_back(x0 - x, y0 - y);

        if (x != y)
        {
            points.emplace_back(x0 + y, y0 + x);
            points.emplace_back(x0 - y, y0 + x);
            points.emplace_back(x0 + y, y0 - x);
            points.emplace_back(x0 - y, y0 - x);
        }
    }
    if (fill)
    {
        x = 0;
        y = radius;
        d = 3 - 2 * radius;
        while (x <= y) {
            for (int i = x0 - x; i <= x0 + x; i++)
            {
                points.emplace_back(i, y0 + y);
                points.emplace_back(i, y0 - y);
            }
            for (int i = x0 - y; i <= x0 + y; i++)
            {
                points.emplace_back(i, y0 + x);
                points.emplace_back(i, y0 - x);
            }
            if (d < 0)
            {
                d += 4 * x + 6;
            }
            else
            {
                d += 4 * (x - y) + 10;
                y--;
            }
            x++;
        }
    }
    return points;
}

std::vector<point> mid_point_algorithm::raster(const square& square, bool fill, view* view_transformation, perspective* perspective_transformation, viewport* viewport_transformation)
{
    std::vector<point> points;
    vector4 a = vector4(square.get_a().get_x(), square.get_a().get_y(), square.get_a().get_z(), 1);
    vector4 b = vector4(square.get_b().get_x(), square.get_b().get_y(), square.get_b().get_z(), 1);
    vector4 c = vector4(square.get_c().get_x(), square.get_c().get_y(), square.get_c().get_z(), 1);
    vector4 d = vector4(square.get_d().get_x(), square.get_d().get_y(), square.get_d().get_z(), 1);
    a = view_transformation->transform(a);
    b = view_transformation->transform(b);
    c = view_transformation->transform(c);
    d = view_transformation->transform(d);
    a = perspective_transformation->transform(a);
    b = perspective_transformation->transform(b);
    c = perspective_transformation->transform(c);
    d = perspective_transformation->transform(d);
   /* point a_final = viewport_transformation->transform(a);
    point b_final = viewport_transformation->transform(b);
    point c_final = viewport_transformation->transform(c);
    point d_final = viewport_transformation->transform(d);*/

    point a_final = point(square.get_a().get_x(), square.get_a().get_y());
    point b_final = point(square.get_b().get_x(), square.get_b().get_y());
    point c_final = point(square.get_c().get_x(), square.get_c().get_y());
    point d_final = point(square.get_d().get_x(), square.get_d().get_y());

    line* ab = new line(a_final.to_vector2(), b_final.to_vector2());
    line* cb = new line(c_final.to_vector2(), b_final.to_vector2());
    line* dc = new line(d_final.to_vector2(), c_final.to_vector2());
    line* da = new line(d_final.to_vector2(), a_final.to_vector2());

    std::vector<point> points_ab = raster(*ab);
    std::vector<point> points_bc = raster(*cb);
    std::vector<point> points_cd = raster(*dc);
    std::vector<point> points_da = raster(*da);
    points.insert(points.end(), points_ab.begin(), points_ab.end());
    points.insert(points.end(), points_bc.begin(), points_bc.end());
    points.insert(points.end(), points_cd.begin(), points_cd.end());
    points.insert(points.end(), points_da.begin(), points_da.end());
    

    /*point a_final = point(square.get_a().get_x(), square.get_a().get_y());
    point b_final = point(square.get_b().get_x(), square.get_b().get_y());
    point c_final = point(square.get_c().get_x(), square.get_c().get_y());
    point d_final = point(square.get_d().get_x(), square.get_d().get_y());
    //arista ab
    for (int i = a_final.x; i <= b_final.x; i++)
    {
        points.emplace_back(i, a_final.y);
    }
    //arista bc
    for (int i = b_final.y; i <= c_final.y; i++)
    {
        points.emplace_back(b_final.x, i);
    }
    //arista cd
    for (int i = c_final.x; i >= d_final.x; i--)
    {
        points.emplace_back(i, c_final.y);
    }
    //arista da
    for (int i = d_final.y; i >= a_final.y; i--)
    {
        points.emplace_back(d_final.x, i);
    }
    if(fill)
    {
        for (int i = a_final.y + 1; i < c_final.y; i++)
        {
            for (int j = a_final.x + 1; j < b_final.x; j++)
            {
                points.emplace_back(j, i);
            }
        }
    }*/
    return points;
}

