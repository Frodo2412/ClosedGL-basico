#pragma once
#include <array>

#include "square.h"
#include "vector3.h"

class cube
{
    vector3 a_, b_, c_, d_, e_, f_, g_, h_;

public:
    explicit cube(const float size, const vector3& center)
    {
        a_ = vector3(center.get_x() - size / 2, center.get_y() - size / 2, center.get_z() - size / 2);
        b_ = vector3(center.get_x() + size / 2, center.get_y() - size / 2, center.get_z() - size / 2);
        c_ = vector3(center.get_x() + size / 2, center.get_y() + size / 2, center.get_z() - size / 2);
        d_ = vector3(center.get_x() - size / 2, center.get_y() + size / 2, center.get_z() - size / 2);
        e_ = vector3(center.get_x() - size / 2, center.get_y() - size / 2, center.get_z() + size / 2);
        f_ = vector3(center.get_x() + size / 2, center.get_y() - size / 2, center.get_z() + size / 2);
        g_ = vector3(center.get_x() + size / 2, center.get_y() + size / 2, center.get_z() + size / 2);
        h_ = vector3(center.get_x() - size / 2, center.get_y() + size / 2, center.get_z() + size / 2);
    }

    std::array<square, 6> get_faces() const;
};
