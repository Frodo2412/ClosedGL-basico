#include "mid_point_algorithm.h"

#include <cmath>
#include <vector>

int to_int(const float x)
{
    return static_cast<int>(std::round(x));
}

std::vector<point> mid_point_algorithm::raster(const line& line)
{
    std::vector<point> points;

    const auto start = line.get_start();
    const auto end = line.get_end();

    const auto a = line.get_dy();
    const auto b = -line.get_dx();

    const int x0 = to_int(start.get_x());
    const auto y0 = to_int(start.get_y());

    points.emplace_back(x0, y0);

    int y = y0;

    auto d = a + b / 2;
    for (int x = x0; static_cast<float>(x) < end.get_x(); x++)
    {
        if (d < 0)
        {
            d += a;
        }
        else
        {
            d += a + b;
            y++;
        }
        points.emplace_back(x, y);
    }

    return points;
}

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
