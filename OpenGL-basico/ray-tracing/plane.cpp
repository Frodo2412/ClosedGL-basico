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
        point = rayo.get_origin() + ray_n * t;
        return true;
    }
}

plane::~plane()
{
    
}
