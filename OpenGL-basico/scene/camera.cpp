#include "camera.h"

vector3 camera::get_position() const
{
    return position_;
}

vector3 camera::get_up() const
{
    return up_;
}

vector3 camera::get_direction() const
{
    return direction_;
}

vector3 camera::get_U() const
{
    return U_;
}

vector3 camera::get_V() const
{
    return V_;
}

double camera::get_aspect_ratio() const
{
    return aspect_ratio_;
}

double camera::get_horizontal_size() const
{
    return horizontal_size_;
}

double camera::get_length() const
{
    return length_;
}

void camera::generate_ray(double u, double v, ray& ray)
{
    //coordenadas en el plano de la camara (lo que vendrian a ser los pixeles por los que pasan los rayos)
    vector3 pixel = camera_centre_ + (U_ * u);
    pixel = pixel + (V_ * v);

    //el rayo va desde la **posicion**(no el centro donde se ubican U y V) de la camara y pasa por el pixel
    ray.set_origin(position_);
    ray.set_direction(pixel);
}
