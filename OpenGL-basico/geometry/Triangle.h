#pragma once
#include "vector3.h"

class triangle
{
    vector3 a_, b_, c_;

public:
    // Constructor
    explicit triangle(const vector3& a = vector3(0, 0, 0), const vector3& b = vector3(0, 0, 0),
                      const vector3& c = vector3(0, 0, 0)) : a_(a), b_(b), c_(c)
    {
    }

    explicit triangle(const vector3& a)
    {
        const auto angle = a.angle_with(vector3(1, 0, 0));
    }

    // Getter methods for the vertexes
    vector3 get_a() const;
    vector3 get_b() const;
    vector3 get_c() const;

    // Setter methods for the coordinates
    void set_a(const vector3& new_a);
    void set_b(const vector3& new_b);
    void set_c(const vector3& new_c);

    void move(const vector3& other);
    void move_left(float distance);
};
