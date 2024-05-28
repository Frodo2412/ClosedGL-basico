#include "viewport.h"

vector3 viewport::to_NDC(vector4 vector)
{
    float x_ndc = vector.get_x()/vector.get_w();
    float y_ndc = vector.get_y()/vector.get_w();
    float z_ndc = vector.get_z()/vector.get_w();
    vector3 res  = vector3(x_ndc, y_ndc, z_ndc);
    return res;
}


point viewport::transform(vector4 vector)
{
    vector3 aux = to_NDC(vector);
    float x = ((aux.get_x() + 1)/2) * width_ + origin_.x;
    float y = ((aux.get_y() + 1)/2) * height_ + origin_.y;
    point res = point(x, y);
    return res;
}
