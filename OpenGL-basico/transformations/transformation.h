#pragma once
#include <initializer_list>

#include "../geometry/vector4.h"

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
    virtual vector4 transform(const vector4& vector) const;
    transformation* operator>>(transformation* other);
};
