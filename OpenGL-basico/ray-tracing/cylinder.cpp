#include "cylinder.h"
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
    vector3 d = rayo.get_direction().normalize(); // Direccion normalizada del rayo
    vector3 m = rayo.get_origin() - get_position(); // Vector desde el origen del cilindro al origen del rayo
    vector3 n = axis_.normalize(); // Eje del cilindro (ya normalizado)

    // Proyecciones sobre el eje del cilindro
    double md = m.dot_product(n);
    double nd = d.dot_product(n);

    // Coeficiente cuadrático
    double a = d.dot_product(d) - nd * nd; // d.dot_product(d) = dx^2 + dy^2 + dz^2
    //Elimino la componente de la dirección del rayo que está alineada con el eje del cilindro.
    //Es útil para determinar si el rayo intersecta el cilindro o no,
    //al considerar solo las componentes del rayo que están perpendiculares al eje del cilindro

    // Coeficiente lineal
    double b = 2.0 * (m.dot_product(d) - md * nd);
    // Coeficiente constante
    double c = m.dot_product(m) - md * md - radius_ * radius_; // m.dot_product(m) = mx^2 + my^2 + mz^2
    
    double discriminant = (b * b) - 4 * a * c;
    if (discriminant < 0.0)
    {
        return false; // No hay intersección
    }

    double sqrt_discriminant = sqrt(discriminant);
    double t1 = (-b - sqrt_discriminant) / (2.0 * a);
    double t2 = (-b + sqrt_discriminant) / (2.0 * a);

    if (t2 < 0.0)
    {
        return false; // Cilindro está detrás del origen del rayo
    }

    double t;
    if (t1 < 0.0)
    {
        t = t2;
    }
    else
    {
        t = t1;
    }
    vector3 hit_point = rayo.get_origin() + d * t;
    double hit_height = (hit_point - get_position()).dot_product(n);

    // Verificar si el punto de intersección está dentro del cilindro
    if (hit_height >= 0.0 && hit_height <= height_)
    {
        point = hit_point;
        vector3 hit_normal = (hit_point - get_position()) - n * hit_height;
        normal = hit_normal.normalize();
        return true;
    }

    // Verificar intersección con las tapas
    double t_cap;
    if (hit_height < 0.0)
    {
        t_cap = -md / nd; // Intersección con la tapa inferior
        normal = -n;
    }
    else       
    {
        t_cap = (height_ - md) / nd; // Intersección con la tapa superior
        normal = n;
    }

    if (t_cap < 0.0)
    {
        return false; // La tapa está detrás del origen del rayo
    }

    hit_point = rayo.get_origin() + d * t_cap;

    // Verificar si el punto está dentro del radio de la tapa
    vector3 hit_point_base;
    if (hit_height < 0.0)
    {
        hit_point_base = hit_point - get_position();
    }
    else
    {
        hit_point_base = hit_point - get_position() - n * height_;
    }
    if (hit_point_base.dot_product(hit_point_base) > radius_ * radius_)
    {
        return false;
    }

    point = hit_point;
    return true;
}