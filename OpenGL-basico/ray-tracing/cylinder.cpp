#include "cylinder.h"

#include <iostream>

// La ecuación de un cilindro finito en el eje z es: x^2 + y^2 = r^2, 0 <= z <= h
// Donde r es el radio del cilindro y h es la altura del cilindro
// para hallar la intersección de un rayo r = R0 + t * d, donde R0 es el origen y d la dirección
// con el cilindro sustituyo en la ec.:
// (R0x + t * dx)^2 + (R0y + t * dy)^2 = r^2
// (R0x^2 + 2 R0x * t * dx + t^2 * dx^2) + (R0y^2 + 2 R0y * t * dy + t^2 * dy^2) = r^2
// (dx^2 + dy^2) * t^2 + 2 * (R0x * dx + R0y * dy) * t + (R0x^2 + R0y^2 - r^2) = 0
// esto es: a * t^2 + b * t + c = 0, donde:
// a = dx^2 + dy^2
// b = 2 * (R0x * dx + R0y * dy)
// c = R0x^2 + R0y^2 - r^2
// Donde t son las posibles intersecciones del rayo con el cilindro.

bool cylinder::test_intersection(ray& rayo, vector3& point, vector3& normal)
{
    vector3 d = rayo.get_direction();
    vector3 o = rayo.get_origin() - position_;

    double a = std::pow(d.x, 2) + std::pow(d.z, 2);
    double b = 2 * (o.x * d.x + o.z * d.z);
    double c = std::pow(o.x, 2) + std::pow(o.z, 2) - std::pow(radius_, 2);

    double discriminant = std::pow(b, 2) - 4 * a * c;

    if (discriminant < 0)
    {
        return false;
    }

    double sqrt_discriminant = std::sqrt(discriminant);
    double t1 = (-b - sqrt_discriminant) / (2 * a);
    double t2 = (-b + sqrt_discriminant) / (2 * a);

    if (t1 >= t2) { std::swap(t1, t2); }

    vector3 p1 = rayo.get_origin() + d * t1;


    if (p1.y >= position_.y && p1.y <= height_ + position_.y)
    {
        point = p1;
        vector3 local_point = p1 - position_;
        vector3 hit_normal = vector3(local_point.x, 0, local_point.z).normalize();
        normal = hit_normal;
        return true;
    }

    // Top test intersection

    if (p1.y > height_ + position_.y)
    {
        if (top_.test_intersection(rayo, point, normal))
        {
            return std::pow((point.x - position_.x), 2) + std::pow((point.z - position_.z), 2) <= std::pow(radius_, 2);
        }
    }

    if (p1.y < position_.y)
    {
        if (bottom_.test_intersection(rayo, point, normal))
        {
            return std::pow((point.x - position_.x), 2) + std::pow((point.z - position_.z), 2) <= std::pow(radius_, 2);
        }
    }

    return false;
}
