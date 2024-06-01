#include "mid_point_algorithm.h"

#include <cmath>
#include <iostream>
#include <vector>


int to_int(const float x)
{
    return static_cast<int>(std::round(x));
}

std::vector<point> mid_point_x_major_upwards(const line& line)
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

std::vector<point> mid_point_x_major_downwards(const line& line)
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

std::vector<point> mid_point_y_major_upwards(const line& line)
{
    std::vector<point> points;

    const auto start = line.get_start();
    const auto end = line.get_end();

    const auto a = line.get_dx();
    const auto b = -line.get_dy();

    const int y0 = to_int(start.y);
    const auto x0 = to_int(start.x);

    points.emplace_back(x0, y0);

    int x = x0;

    auto d = a + b / 2;
    for (int y = y0; static_cast<float>(y) < end.y; y++)
    {
        if (d < 0) { d += a; }
        else
        {
            d += a + b;
            x++;
        }
        points.emplace_back(x, y);
    }

    return points;
}

std::vector<point> mid_point_y_major_downwards(const line& line)
{
    std::vector<point> points;

    const auto start = line.get_start();
    const auto end = line.get_end();

    const auto a = line.get_dx();
    const auto b = -line.get_dy();

    const int y0 = to_int(start.y);
    const auto x0 = to_int(start.x);

    points.emplace_back(x0, y0);

    int x = x0;

    auto d = a + b / 2;
    for (int y = y0; static_cast<float>(y) < end.y; y++)
    {
        if (d > 0) { d += a; }
        else
        {
            d += a + b;
            x--;
        }
        points.emplace_back(x, y);
    }

    return points;
}

std::vector<point> mid_point_algorithm::raster(const line& line)
{
    const auto start = line.get_start();
    const auto end = line.get_end();

    const auto dx = std::abs(line.get_dx());
    const auto dy = std::abs(line.get_dy());

    if (dx >= dy)
    {
        if (start.y <= end.y) { return mid_point_x_major_upwards(line); }
        return mid_point_x_major_downwards(line);
    }
    else
    {
        if (start.x <= end.x) { return mid_point_y_major_upwards(line); }
        return mid_point_y_major_downwards(line);
    }
}
