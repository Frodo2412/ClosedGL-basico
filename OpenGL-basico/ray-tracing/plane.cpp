#include "plane.h"


bool plane::test_intersection(ray& rayo, vector3& point, vector3& normal)
{
    vector3 ray_n = rayo.get_direction().normalize();
    double denominador = normal_.dot_product(ray_n);

    // Verificación del denominador cercano a cero
    if (fabs(denominador) < 1e-6) 
    {
        return false;
    }

    vector3 aux = get_position() - rayo.get_origin();
    double t = normal_.dot_product(aux) / denominador;

    if (t > 0.0) // El punto de intersección está delante del origen del rayo
    {
        vector3 aux_p = rayo.get_origin() + ray_n * t; // Punto de intersección
        vector3 pt = aux_p - get_position();

        double u = 0, v = 0;

        if (normal_ == vector3(1, 0, 0) || normal_ == vector3(-1, 0, 0))
        {
            u = (pt.get_y() * V_.get_z() - pt.get_z() * V_.get_y()) / (U_.get_y() * V_.get_z() - U_.get_z() * V_.get_y());
            v = (pt.get_z() * U_.get_y() - pt.get_y() * U_.get_z()) / (U_.get_y() * V_.get_z() - U_.get_z() * V_.get_y());
        }
        else if (normal_ == vector3(0, 1, 0) || normal_ == vector3(0, -1, 0))
        {
            u = (pt.get_x() * V_.get_z() - pt.get_z() * V_.get_x()) / (U_.get_x() * V_.get_z() - U_.get_z() * V_.get_x());
            v = (pt.get_z() * U_.get_x() - pt.get_x() * U_.get_z()) / (U_.get_x() * V_.get_z() - U_.get_z() * V_.get_x());
        }
        else if (normal_ == vector3(0, 0, 1) || normal_ == vector3(0, 0, -1))
        {
            u = (pt.get_x() * V_.get_y() - pt.get_y() * V_.get_x()) / (U_.get_x() * V_.get_y() - U_.get_y() * V_.get_x());
            v = (pt.get_y() * U_.get_x() - pt.get_x() * U_.get_y()) / (U_.get_x() * V_.get_y() - U_.get_y() * V_.get_x());
        }

        if (fabs(u) <= width_ && fabs(v) <= height_)
        {
            point.set_x(aux_p.get_x());
            point.set_y(aux_p.get_y());
            point.set_z(aux_p.get_z());
            vector3 aux_norm = normal_.normalize(); // Normal del plano = normal en el punto de intersección
            normal.set_x(aux_norm.get_x());
            normal.set_y(aux_norm.get_y());
            normal.set_z(aux_norm.get_z());
            return true;
        }
    }
    return false;
}

plane::~plane()
{
}
