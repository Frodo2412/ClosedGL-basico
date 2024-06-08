#pragma once
#include <ostream>

struct vector2
{
    double x, y;

    vector2(double x, double y);
    double get_x() const;
    double get_y() const;

    friend std::ostream& operator<<(std::ostream& os, const vector2& v);
};
