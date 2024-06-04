#pragma once

#include <cmath>

struct vector3
{
    float x, y, z;

    float length = x * x + y * y + z * z;
    float magnitude = std::sqrt(length);

    vector3(const float x = 0.0, const float y = 0.0, const float z = 0.0) : x(x), y(y), z(z)
    {
    }

    // Getter methods for the coordinates
    float get_x() const;
    float get_y() const;
    float get_z() const;


    // Setter methods for the coordinates
    void set_x(float new_x);
    void set_y(float new_y);
    void set_z(float new_z);

    // Operators
    vector3 operator+(const vector3& other) const;
    void operator+=(const vector3& other);
    vector3 operator -(const vector3& other) const;
    void operator-=(const vector3& other);
    vector3 operator*(float s) const;
    vector3 operator*(const vector3& other) const;
    vector3 operator/(int s) const;
    vector3 operator-() const;

    bool operator==(const vector3& zero) const;

    float dot_product(const vector3& other) const;
    float angle_with(const vector3& other) const; // returns in radians

    vector3 normalize() const;
    vector3 symmetrical(const vector3& other) const;

    static vector3 zero();
    void print() const;
    void reset();
};
