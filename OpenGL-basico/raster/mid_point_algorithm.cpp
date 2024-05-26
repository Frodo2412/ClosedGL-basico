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

std::vector<point> mid_point_algorithm::raster(const circle& circle)
{
    std::vector<point> points;

    const int x0 = to_int(circle.center.get_x());
    const int y0 = to_int(circle.center.get_y());
    const int radius = to_int(circle.radius);

    int x = radius;
    int y = 0;
    int d = 1 - radius;

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

    return points;
}
