#include "plane.h"


bool plane::test_intersection(ray& rayo, vector3& point, vector3& normal, color& color)
{
    vector3 ray_n = rayo.get_direction().normalize();
    float denominador = normal_.dot_product(ray_n);
    const float epsilon = 1e-6;
    if (std::abs(denominador) < epsilon)
    {
        return false;
    } else
    {
        vector3 aux = get_position() - rayo.get_origin();
        float t = normal_.dot_product(aux)/denominador;
        if(t < 0.0f)
        {
            return false;
        }
        vector3 aux_p = rayo.get_origin() + ray_n * t;
        point.set_x(aux_p.get_x());
        point.set_y(aux_p.get_y());
        point.set_z(aux_p.get_z());
        vector3 aux_norm = normal_.normalize();
        normal.set_x(aux_norm.get_x());
        normal.set_y(aux_norm.get_y());
        normal.set_z(aux_norm.get_z());
        return true;
    }
}

plane::~plane()
{
    
}
