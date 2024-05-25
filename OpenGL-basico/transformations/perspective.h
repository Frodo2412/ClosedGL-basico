#pragma once
#include <cmath>

#include "transformation.h"

class perspective final : public transformation
{
public:
    explicit perspective(const float fov, const float aspect, const float near, const float far)
        : transformation(
            {
                1 / (aspect * tan(fov / 2)), 0, 0, 0,
                0, 1 / tan(fov / 2), 0, 0,
                0, 0, (far + near) / (near - far), 2 * far * near / (near - far),
                0, 0, -1, 0
            }

        )
    {
    }
};
