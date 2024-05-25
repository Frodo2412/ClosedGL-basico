#include "view.h"

view::view(const camera& camera)
{
    const vector3 position = camera.get_position();
    const vector3 direction = camera.get_direction();
    const vector3 up = camera.get_up().normalize();
    const vector3 forward = direction.normalize();
    const vector3 right = (up * forward).normalize();

    const float ret[4][4] = {
        {right.get_x(), up.get_x(), -forward.get_x(), 0},
        {right.get_y(), up.get_y(), -forward.get_y(), 0},
        {right.get_z(), up.get_z(), -forward.get_z(), 0},
        {-position.dot_product(right), -position.dot_product(up), forward.dot_product(position), 1}
    };

    for (auto i = 0; i < 4; ++i)
        for (auto j = 0; j < 4; ++j)
            matrix_[i][j] = ret[i][j];
}
