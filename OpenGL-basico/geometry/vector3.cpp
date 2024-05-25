#include "vector3.h"

float vector3::get_x() const { return x_; }
float vector3::get_y() const { return y_; }
float vector3::get_z() const { return z_; }

float vector3::magnitude() const
{
    return magnitude_;
}

void vector3::set_x(const float new_x) { x_ = new_x; }
void vector3::set_y(const float new_y) { y_ = new_y; }
void vector3::set_z(const float new_z) { z_ = new_z; }

vector3 vector3::operator+(const vector3& other) const
{
    return vector3(x_ + other.get_x(), y_ + other.get_y(), z_ + other.get_z());
}

void vector3::operator+=(const vector3& other)
{
    x_ += other.get_x();
    y_ += other.get_y();
    z_ += other.get_z();
}

vector3 vector3::operator -(const vector3& other) const
{
    return vector3(x_ - other.x_, y_ - other.y_, z_ - other.z_);
}

void vector3::operator-=(const vector3& other)
{
    x_ -= other.x_;
    y_ -= other.y_;
    z_ -= other.z_;
}

vector3 vector3::operator*(const float s) const
{
    return vector3(x_ * s, y_ * s, z_ * s);
}

vector3 vector3::operator*(const vector3& other) const
{
    return vector3(
        y_ * other.z_ - z_ * other.y_, // Calculate c1
        z_ * other.x_ - x_ * other.z_, // Calculate c2
        x_ * other.y_ - y_ * other.x_ // Calculate c3
    );
}


vector3 vector3::operator/(const int s) const
{
    return vector3(x_ / s, y_ / s, z_ / s);
}

vector3 vector3::operator-() const
{
    return vector3(-x_, -y_, -z_);
}

float vector3::dot_product(const vector3& other) const
{
    return x_ * other.x_ + y_ * other.y_ + z_ * other.z_;
}

float vector3::angle_with(const vector3& other) const
{
    const auto numerator = this->dot_product(other);
    const auto denominator = this->magnitude_ * other.magnitude_;

    const auto cosine = numerator / denominator;

    return std::acos(cosine);
}

vector3 vector3::normalize() const
{
    return vector3(x_ / magnitude_, y_ / magnitude_, z_ / magnitude_);
}

vector3 vector3::symmetrical(const vector3& other) const
{
    const auto normalized_other = other.normalize();
    const auto aux = normalized_other * (2 * normalized_other.dot_product(*this));
    return aux - *this;
}

vector3 vector3::zero()
{
    return vector3(0, 0, 0);
}

void vector3::reset()
{
    x_ = 0;
    y_ = 0;
    z_ = 0;
}
