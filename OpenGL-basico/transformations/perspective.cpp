#include "perspective.h"
#include <cmath>

perspective::perspective(const float fov, const float aspect_ratio, const float near, const float far)
{
    const float tan_half_fov = std::tan(fov / 2.0f);
    const float res[4][4] = {
        {1.0f / (aspect_ratio * tan_half_fov), 0, 0, 0},
        {0, 1.0f / (aspect_ratio * tan_half_fov), 0, 0},
        {0, 0, -(far + near) / (far - near), -1},
        {0, 0, -(2 * far * near) / (far - near), 0}
    };

    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            matrix_[i][j] = res[i][j];
}
