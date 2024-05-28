#include "perspective.h"

perspective::perspective(scene * scene)
{
    const float fov = scene->get_camera().get_fov();
    const float aspect_ratio = (float)scene->get_width() / (float)scene->get_heigth();
    const float near = scene->get_camera().get_near();
    const float far = scene->get_camera().get_far();
    const float tan_half_fov = std::tan(fov / 2.0f);
    const float res[4][4] = {
        {1.0f / (aspect_ratio * tan_half_fov), 0, 0, 0},
        {0, 1.0f / tan_half_fov, 0, 0},
        {0, 0, (far + near) / (near - far), 2 * far * near / (near - far)},
        {0, 0, -1, 0}
    };

    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            matrix_[i][j] = res[i][j];
}
