#include "Triangle.h"

vector3 triangle::get_a() const
{
    return a_;
}

vector3 triangle::get_b() const
{
    return b_;
}

vector3 triangle::get_c() const
{
    return c_;
}

void triangle::set_a(const vector3& new_a)
{
    a_ = new_a;
}

void triangle::set_b(const vector3& new_b)
{
    b_ = new_b;
}

void triangle::set_c(const vector3& new_c)
{
    c_ = new_c;
}

void triangle::move(const vector3& other)
{
    a_ = a_ + other;
    b_ = b_ + other;
    c_ = c_ + other;
}

void triangle::move_left(const float distance)
{
    a_.set_x(a_.get_x() + distance);
    b_.set_x(b_.get_x() + distance);
    c_.set_x(c_.get_x() + distance);
}
