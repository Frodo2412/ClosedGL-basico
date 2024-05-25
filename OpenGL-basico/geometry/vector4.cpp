#include "vector4.h"

vector4::vector4(float r, float g, float b, float alpha)
{
    r_ = r;
    g_ = g;
    b_ = b;
    alpha_ = alpha;
}

void vector4::set_r(float r)
{
    r_ = r;
}

void vector4::set_g(float g)
{
    g_ = g;
}

void vector4::set_b(float b)
{
    b_ = b;
}

void vector4::set_alpha(float alpha)
{
    alpha_ = alpha;
}

float vector4::get_r()
{
    return r_;
}

float vector4::get_g()
{
    return g_;
}

float vector4::get_b()
{
    return b_;
}

float vector4::get_alpha()
{
    return alpha_;
}
