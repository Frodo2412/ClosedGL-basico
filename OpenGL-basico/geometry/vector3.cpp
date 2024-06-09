#include "vector3.h"

#include <cstdio>

double vector3::get_x() const { return x; }
double vector3::get_y() const { return y; }
double vector3::get_z() const { return z; }

double vector3::get_length()
{
    return x * x + y * y + z * z;
}

double vector3::get_magnitude()
{
    return std::sqrt(x * x + y * y + z * z);
}

void vector3::set_x(const double new_x) { x = new_x; }
void vector3::set_y(const double new_y) { y = new_y; }
void vector3::set_z(const double new_z) { z = new_z; }

vector3 vector3::operator+(const vector3& other) const
{
    return vector3(x + other.get_x(), y + other.get_y(), z + other.get_z());
}

void vector3::operator+=(const vector3& other)
{
    x += other.get_x();
    y += other.get_y();
    z += other.get_z();
}

vector3 vector3::operator -(const vector3& other) const
{
    return vector3(x - other.x, y - other.y, z - other.z);
}

void vector3::operator-=(const vector3& other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
}

vector3 vector3::operator*(const double s) const
{
    return vector3(x * s, y * s, z * s);
}

vector3 vector3::operator*(const vector3& other) const
{
    return vector3(
        y * other.z - z * other.y, // Calculate c1
        z * other.x - x * other.z, // Calculate c2
        x * other.y - y * other.x // Calculate c3
    );
}


vector3 vector3::operator/(const int s) const
{
    return vector3(x / s, y / s, z / s);
}

vector3 vector3::operator-() const
{
    return vector3(-x, -y, -z);
}

bool vector3::operator==(const vector3& zero) const
{
    return x == zero.x && y == zero.y && z == zero.z;
}

double vector3::dot_product(const vector3& other) const
{
    return x * other.x + y * other.y + z * other.z;
}

vector3 vector3::cross_product(const vector3& other) const
{
    double result_x = this->get_y() * other.get_z() - this->get_z() * other.get_y();
    double result_y = this->get_z() * other.get_x() - this->get_x() * other.get_z();
    double result_z = this->get_x() * other.get_y() - this->get_y() * other.get_x();
    return vector3(result_x, result_y, result_z);
}

double vector3::angle_with(const vector3& other) const
{
    const auto numerator = this->dot_product(other);
    const auto denominator = this->magnitude * other.magnitude;

    const auto cosine = numerator / denominator;

    return std::acos(cosine);
}

vector3 vector3::normalize() const
{
    return vector3(x / magnitude, y / magnitude, z / magnitude);
}

vector3 vector3::symmetrical(const vector3& other) const
{
    const auto normalized_other = other.normalize();
    const auto aux = normalized_other * (2.0 * normalized_other.dot_product(*this));
    return aux - *this;
}

vector3 vector3::zero()
{
    return vector3(0, 0, 0);
}

void vector3::reset()
{
    x = 0;
    y = 0;
    z = 0;
}

void vector3::print() const
{
    printf("\nVECTOR3: (%.2f, %.2f, %.2f)\n", x, y, z);
}

double vector3::get_norm() const
{
    double aux = x * x + y * y + z * z;
    return sqrt(aux);
}

std::ostream& operator<<(std::ostream& os, const vector3& v)
{
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}
