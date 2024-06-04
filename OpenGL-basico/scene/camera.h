#pragma once
#include <iostream>

#include "../geometry/vector3.h"
#include "../ray-tracing/ray.h"
class camera
{
    vector3 position_, look_at_, up_;
    vector3 direction_;
    vector3 U_, V_; //NO ESTAN NORMALIZADOS, REPRESENTAN LAS DIMENSIONES DE LA PANTALLA
    vector3 camera_centre_;
    float fov_; // in radians
    float aspect_ratio_;
    float horizontal_size_;
    float length_;
public:
    explicit camera(const vector3& position, const vector3& look_at, const vector3& up)
        : position_(position), look_at_(look_at), up_(up.normalize())
    {
        fov_ = (float)(2 * 3.141590)/(float)16;
        aspect_ratio_ = (float)4.0 / (float)3.0;
        horizontal_size_ = 400;
        length_ = 100;
        direction_ = (look_at_ - position_).normalize();
        U_ = (direction_ * up_).normalize();
        V_ = (U_ * direction_).normalize();
        U_ = U_ * horizontal_size_;
        V_ = V_ * (horizontal_size_ / aspect_ratio_);
        camera_centre_ = position_ + (direction_ * length_);
        std::cout << "Camara creada" << std::endl;
        std::cout << "Camera Centre: ";
        camera_centre_.print();
        std::cout << "U: ";
        U_.print();
        std::cout << "V: ";
        V_.print();
    }

    float get_fov() const;
    float get_aspect_ratio() const;
    float get_horizontal_size() const;
    float get_length() const;
    vector3 get_position() const;
    vector3 get_direction() const;
    vector3 get_up() const;
    vector3 get_right() const;
    vector3 get_U() const;
    vector3 get_V() const;

    // u, v in [-1, 1], voy actualizando el rayo
    void generate_ray(float u, float v, ray& ray);
};
