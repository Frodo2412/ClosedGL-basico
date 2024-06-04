#include "sphere.h"

#include <iostream>

sphere::~sphere()
{

}

bool sphere::test_intersection(ray &rayo, vector3 &point, vector3 &normal, color &color)
{
    vector3 rayo_n = rayo.get_direction().normalize();

    float a = rayo_n.dot_product(rayo_n);
    
    float b = 2.0f * rayo.get_origin().dot_product(rayo_n);
    
    float c = rayo.get_origin().dot_product(rayo.get_origin()) - 1.0f;
    
    float discriminante = (b*b) - 4.0f * a * c;
    //std::cout << "discriminante: " << discriminante << "\n";

    if (discriminante > 0.0)
    {
        float raiz = sqrtf(discriminante);
        float x1 = (-b + raiz) / 2.0;
        float x2 = (-b - raiz) / 2.0;
        
        if ((x1 < 0.0) || (x2 < 0.0))
        {
            return false;
        }
        if (x1 < x2)
        {
            point = rayo.get_origin() + (rayo_n * x1);
        }
        else
        {
            point = rayo.get_origin() + (rayo_n * x2);
        }
        return true;
    }
    return false;
}
