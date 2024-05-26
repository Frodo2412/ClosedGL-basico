#include "vector4.h"

vector4::vector4(float x, float y, float z, float w) 
{
    x_ = x;
    y_ = y;
    z_ = z;
    w_ = w;
}

float vector4::get_w() const
{
    return w_;
}

float vector4::get_x() const
{
    return x_;
}

float vector4::get_y() const
{
    return y_;
}

float vector4::get_z() const
{
    return z_;
}

void vector4::set_w(float w)
{
    w_ = w;
}

void vector4::set_x(float x)
{
    x_ = x;
}

void vector4::set_y(float y)
{
    y_ = y;
}

void vector4::set_z(float z)
{
    z_ = z;
}