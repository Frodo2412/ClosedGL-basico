#pragma once
#include <initializer_list>

#include "../geometry/vector3.h"

class transformation
{
protected:
    float matrix_[4][4] = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };

    explicit transformation();
    explicit transformation(std::initializer_list<float> values);

public:
    vector3 transform(const vector3& vector) const;
    transformation operator>>(const transformation& other) const;
};
