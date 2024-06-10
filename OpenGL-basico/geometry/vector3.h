#pragma once

#include <cmath>
#include <ostream>

struct vector3
{
    double x, y, z;

    double length = x * x + y * y + z * z;
    double magnitude = std::sqrt(length);

    vector3(const double x = 0.0, const double y = 0.0, const double z = 0.0) : x(x), y(y), z(z)
    {
    }

    // Getter methods for the coordinates
    double get_x() const;
    double get_y() const;
    double get_z() const;

    double get_length();
    double get_magnitude();

    // Setter methods for the coordinates
    void set_x(double new_x);
    void set_y(double new_y);
    void set_z(double new_z);

    // Operators
    vector3 operator+(const vector3& other) const;
    void operator+=(const vector3& other);
    vector3 operator -(const vector3& other) const;
    void operator-=(const vector3& other);
    vector3 operator*(double s) const;
    vector3 operator*(const vector3& other) const;
    vector3 operator/(int s) const;
    vector3 operator-() const;

    bool operator==(const vector3& zero) const;

    double dot_product(const vector3& other) const;
    vector3 cross_product(const vector3& other) const;
    double angle_with(const vector3& other) const; // returns in radians

    vector3 normalize() const;
    vector3 symmetrical(const vector3& other) const;

    static vector3 zero();
    void print() const;
    void reset();

    double get_norm() const;

    friend std::ostream& operator<<(std::ostream& os, const vector3& v);
};
