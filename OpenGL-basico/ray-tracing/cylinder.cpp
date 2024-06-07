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

    vector3 n = axis_; // Eje del cilindro (ya normalizado)

    // Proyecciones sobre el eje del cilindro
    float md = m.dot_product(n);
    float nd = d.dot_product(n);

    // Coeficiente cuadrático
    float a = d.dot_product(d) - nd * nd; // d.dot_product(d) = dx^2 + dy^2 + dz^2
    //Elimino la componente de la dirección del rayo que está alineada con el eje del cilindro.
    //Es útil para determinar si el rayo intersecta el cilindro o no,
    //al considerar solo las componentes del rayo que están perpendiculares al eje del cilindro


    // Coeficiente constante
    float c = m.dot_product(m) - md * md - radius_ * radius_; // m.dot_product(m) = mx^2 + my^2 + mz^2

    // Coeficiente lineal
    float b = 2.0f * (m.dot_product(d) - md * nd);

    float discriminant = (b * b) - 4 * a * c;

    if (discriminant < 0.0f) // Si el discriminante es negativo, no hay intersección
    {
        return false;
    }

    float sqrt_discriminant = sqrtf(discriminant);
    float t1 = (-b - sqrt_discriminant) / (2.0f * a);
    float t2 = (-b + sqrt_discriminant) / (2.0f * a);

    // Si ambos t1 y t2 son negativos, el cilindro está detrás del origen del rayo
    if (t2 < 0.0f)
    {
        return false;
    }

    // Elegimos el menor t positivo
    float t = t1;
    if (t < 0.0f)
    {
        t = t2;
    }

    vector3 hit_point = rayo.get_origin() + d * t; // Punto de intersección candidato

    float hit_height = (hit_point - get_position()).dot_product(n);
    // Proyección del punto de intersección sobre el eje del cilindro

    // Verificación si el punto de intersección está dentro de los límites del cilindro
    if (hit_height < 0.0f || hit_height > height_)
    {
        if (hit_height < 0.0f)
        {
            // Verificamos intersección con las tapas del cilindro
            t = (0.0f - md) / nd;
        }
        else
        {
            t = (height_ - md) / nd;
        }

        if (t < 0.0f) // Si t es negativo, la tapa está detrás del origen del rayo
        {
            return false;
        }

        hit_point = rayo.get_origin() + d * t; // Nuevo punto de intersección con la tapa

        // Verificar si el punto de intersección está dentro del radio de la tapa
        if ((hit_point - get_position()).dot_product((hit_point - get_position())) > radius_ * radius_)
        {
            return false;
        }

        normal = n;
        if (hit_height < 0.0f)
        {
            normal = -n;
        }

        point = hit_point;
        return true;
    }

    point = hit_point;

    // Normal en el punto de intersección en el lado del cilindro
    vector3 hit_normal = (hit_point - get_position()) - n * hit_height;
    normal = hit_normal.normalize();

    return true;
}
