#pragma once

#include "object.h"

class plane : public object
{
    vector3 normal_;
    double A_, B_, C_, D_;
    vector3 U_, V_; //coordenadas de ancho y largo para el plano. las usaremos para limitarlo y que no sea infinito😀 
    double width_;
    double height_;

public:
    plane(vector3 pos, vector3 normal, color color, double width, double height, double reflectivity,
          double shininess) : object(pos, color, reflectivity, shininess)
    {
        width_ = width;
        height_ = height;
        normal_ = normal.normalize();
        A_ = normal_.x;
        B_ = normal_.y;
        C_ = normal_.z;
        D_ = -(pos.x * A_ + pos.y * B_ + pos.z * C_);

        vector3 arbitrary = {0, 0, 1};
        if (normal_ == vector3(0, 0, 1) || normal_ == vector3(0, 0, -1)) //normal_ alineada con el eje z
        {
            arbitrary = {1, 0, 0};
        }
        V_ = (normal_ * arbitrary).normalize();
        U_ = (V_ * normal_).normalize();
    }

    bool test_intersection(ray& rayo, vector3& point, vector3& normal) override;
    ~plane() override;
};
