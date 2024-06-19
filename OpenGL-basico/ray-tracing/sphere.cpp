#include "sphere.h"

#include <iostream>

sphere::~sphere()
{
}

double sphere::get_radius() const
{
    return radius_;
}

bool sphere::test_intersection(ray& rayo, vector3& point, vector3& normal)
{
    vector3 L = rayo.get_origin() - get_position(); // vector desde el centro de la esfera al origen del rayo
    vector3 rayo_n = rayo.get_direction().normalize();

    double a = rayo_n.dot_product(rayo_n);
    double b = 2.0 * L.dot_product(rayo_n);
    double c = L.dot_product(L) - radius_ * radius_;
    double discriminante = (b * b) - 4.0 * a * c;

    if (discriminante < 0.0)
    {
        return false; // No hay intersección
    }

    double sqrt_discriminante = sqrt(discriminante);
    double t1 = (-b - sqrt_discriminante) / (2.0 * a);
    double t2 = (-b + sqrt_discriminante) / (2.0 * a);

    // Verificar si ambos puntos están detrás del origen del rayo
    if (t1 < 0.0 && t2 < 0.0)
    {
        return false;
    }

    double t;
    if (t1 > 0.0 && t2 > 0.0)
    {
        t = std::min(t1, t2); // Ambos puntos están delante del origen, escoger el más cercano
    }
    else
    {
        t = std::max(t1, t2); // Solo uno está delante del origen, escoger el positivo
    }

    point = rayo.get_origin() + rayo_n * t;
    normal = (point - get_position()).normalize();
    return true;
}

