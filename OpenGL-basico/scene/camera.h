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
    int width_, height_;
    double aspect_ratio_;
    double horizontal_size_;
    double length_;

public:
    explicit camera(const vector3& position, const vector3& look_at, const vector3& up, int width, int height)
        : position_(position), look_at_(look_at), up_(up.normalize()), width_(width), height_(height)
    {
        aspect_ratio_ = static_cast<double>(width_) / static_cast<double>(height_);
        horizontal_size_ = static_cast<double>(width_) / 2;
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

    double get_aspect_ratio() const;
    double get_horizontal_size() const;
    double get_length() const;
    vector3 get_position() const;
    vector3 get_direction() const;
    vector3 get_up() const;
    vector3 get_U() const;
    vector3 get_V() const;

    // u, v in [-1, 1], voy actualizando el rayo
    void generate_ray(double u, double v, ray& ray);
};
