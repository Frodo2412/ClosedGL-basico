#include "sphere.h"

#include <iostream>

sphere::~sphere()
{

}

double sphere::get_radius() const
{
    return radius_;
}

bool sphere::test_intersection(ray &rayo, vector3 &point, vector3 &normal)
{
    vector3 L = rayo.get_origin() - get_position();//vector desde el centro de la esfera al origen del rayo
    
    vector3 rayo_n = rayo.get_direction().normalize();

    double a = rayo_n.dot_product(rayo_n);
    
    double b = 2.0 * L.dot_product(rayo_n);
    
    double c =L.dot_product(L) - radius_*radius_;
    
    double discriminante = (b*b) - 4.0 * a * c;

    if (discriminante >= 0.0)
    {
        double raiz = sqrt(discriminante);
        double x1 = (-b + raiz) / 2.0;
        double x2 = (-b - raiz) / 2.0;
        
        if ((x1 < 0.0) || (x2 < 0.0)) //si las intersecciones estan detras del origen del rayo
        {
            return false;
        }
        /* Cuando se intersecta el rayo en 2 puntos nos quedamos con el que este mas cerca */
        if (x1 < x2)
        {
            vector3 aux = (rayo.get_origin() + (rayo_n * x1));
            point.set_x(aux.get_x());
            point.set_y(aux.get_y());
            point.set_z(aux.get_z());
        }
        else
        {
            vector3 aux = (rayo.get_origin() + (rayo_n * x2));
            point.set_x(aux.get_x());
            point.set_y(aux.get_y());
            point.set_z(aux.get_z());
        }
        vector3 aux_norm = (point - get_position()).normalize();
        normal.set_x(aux_norm.get_x());
        normal.set_y(aux_norm.get_y());
        normal.set_z(aux_norm.get_z());
        return true;
    }
    return false;
}
