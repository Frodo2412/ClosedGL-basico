#include "plane.h"


bool plane::test_intersection(ray& rayo, vector3& point, vector3& normal)
{
    vector3 ray_n = rayo.get_direction().normalize();
    float denominador = normal_.dot_product(ray_n);
    const float epsilon = 1e-21;
    if (std::abs(denominador) < epsilon)
    {
        return false;
    } else
    {
        vector3 aux = get_position() - rayo.get_origin();
        float t = normal_.dot_product(aux)/denominador;
        if(t > 0.0f)
        {
            vector3 aux_p = rayo.get_origin() + ray_n * t;//punto de interseccion
            vector3 pt = aux_p - get_position();
            
            float u = (pt.get_z() * V_.get_x() - pt.get_x() * V_.get_z()) / (U_.get_z() * V_.get_x() - U_.get_x() * V_.get_z());
            float v = (pt.get_x() * U_.get_z() - pt.get_z() * U_.get_x()) / (U_.get_z() * V_.get_x() - U_.get_x() * V_.get_z());
            
            //casos donde el denominador puede ser 0, son justamente cuando la normal es paralela a los ejes x, y o z
            
            if(normal_ == vector3(1,0,0) || normal_ == vector3(-1,0,0))
            {
                u = (pt.get_y() * V_.get_z() - pt.get_z() * V_.get_y())/(U_.get_y() * V_.get_z() - U_.get_z() * V_.get_y());
                v = (pt.get_z() * U_.get_y() - pt.get_y() * U_.get_z())/(U_.get_y() * V_.get_z() - U_.get_z() * V_.get_y());
            }
            if(normal_ == vector3(0,1,0) || normal_ == vector3(0,-1,0))
            {
                u = (pt.get_x() * V_.get_z() - pt.get_z() * V_.get_x()) / (U_.get_x() * V_.get_z() - U_.get_z() * V_.get_x());
                v = (pt.get_z() * U_.get_x() - pt.get_x() * U_.get_z()) / (U_.get_x() * V_.get_z() - U_.get_z() * V_.get_x());
            }
            if(normal_ == vector3(0,0,1) || normal_ == vector3(0,0,-1))
            {
                u = (pt.get_x() * V_.get_y() - pt.get_y() * V_.get_x()) / (U_.get_x() * V_.get_y() - U_.get_y() * V_.get_x());
                v = (pt.get_y() * U_.get_x() - pt.get_x() * U_.get_y()) / (U_.get_x() * V_.get_y() - U_.get_y() * V_.get_x());
            }

            if(abs(u) <= width_ && abs(v) <= height_) 
            {
                point.set_x(aux_p.get_x());
                point.set_y(aux_p.get_y());
                point.set_z(aux_p.get_z());
                vector3 aux_norm = normal_.normalize();//normal del plano = normal en el punto de interseccopn
                normal.set_x(aux_norm.get_x());
                normal.set_y(aux_norm.get_y());
                normal.set_z(aux_norm.get_z());
                return true;
            }
        }
        return false;
    }
}

plane::~plane()
{
    
}
