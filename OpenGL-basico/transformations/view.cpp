#include "view.h"

view::view(const camera& camera)
{
    const vector3 position = camera.get_position();
    const vector3 up = camera.get_up();
    const vector3 forward = camera.get_forward();
    const vector3 right = camera.get_right();

    const float ret[4][4] = {
        {right.get_x(), right.get_y(), right.get_z(), - right.dot_product(position)},
        {up.get_x(), up.get_y(), up.get_z(), - up.dot_product(position)},
        {- forward.get_x(), - forward.get_y(), - forward.get_z(), forward.dot_product(position)},
        {0, 0, 0, 1}
    };
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            matrix_[i][j] = ret[i][j];
        }
    }
}
