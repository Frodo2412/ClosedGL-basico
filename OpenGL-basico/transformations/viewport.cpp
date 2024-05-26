#include "viewport.h"

void viewport::to_NDC(vector4 vector)
{
    float x_ndc = vector.get_x()/vector.get_w();
    float y_ndc = vector.get_y()/vector.get_w();
    float z_ndc = vector.get_z()/vector.get_w();
    vector.set_x(x_ndc);
    vector.set_y(y_ndc);
    vector.set_z(z_ndc);
}


point viewport::transform(vector4 vector)
{
    to_NDC(vector);
    float x = ((vector.get_x() + 1)/2) * width_ + origin_.x;
    float y = ((vector.get_y() + 1)/2) * height_ + origin_.y;
    point res = point(x, y);
    return res;
}
