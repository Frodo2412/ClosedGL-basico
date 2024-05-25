#pragma once
#include <initializer_list>

#include "../geometry/vector3.h"

class transformation
{
    float matrix_[4][4] = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };

protected:
    explicit transformation(const std::initializer_list<float> values)
    {
        auto it = values.begin();
        for (auto& i : matrix_)
            for (float& j : i)
                j = *it++;
    }

    vector3 transform(const vector3& vector) const
    {
        return vector3{
            matrix_[0][0] * vector.get_x() + matrix_[0][1] * vector.get_y() + matrix_[0][2] * vector.get_z() + matrix_[
                0][3],
            matrix_[1][0] * vector.get_x() + matrix_[1][1] * vector.get_y() + matrix_[1][2] * vector.get_z() + matrix_[
                1][3],
            matrix_[2][0] * vector.get_x() + matrix_[2][1] * vector.get_y() + matrix_[2][2] * vector.get_z() + matrix_[
                2][3]
        };
    }
};
