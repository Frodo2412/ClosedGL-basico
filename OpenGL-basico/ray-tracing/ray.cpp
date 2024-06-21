#include "ray.h"

vector3 ray::get_origin() const
{
    return origin_;
}

vector3 ray::get_direction() const
{
    return direction_;
}

vector3 ray::get_ray_vector() const
{
    return direction_ - origin_;
}

void ray::set_origin(vector3 origin)
{
    origin_ = origin;
}

void ray::set_direction(vector3 dir)
{
    direction_ = dir;
}

ray ray::reflect(const vector3& intersection_point, const vector3& intersection_normal) const
{
    const vector3 view_dir = get_ray_vector();
    const vector3 normal = intersection_normal;
    vector3 reflected_dir = view_dir - 2 * normal * view_dir.dot_product(normal);

    return {intersection_point + reflected_dir * 0.00001, reflected_dir};
}

ray ray::refract(const vector3& intersection_point, const vector3& intersection_normal,
                 double get_refractive_index) const
{
    const vector3 incident_ray = this->get_direction().normalize();
    const vector3 normal = intersection_normal.normalize();

    const double n1 = 1.0; // Assuming the incident medium is air with refractive index 1
    const double n2 = get_refractive_index;

    double cos_i = -incident_ray.dot_product(normal);
    double sin_t2 = (n1 / n2) * (n1 / n2) * (1.0 - cos_i * cos_i);

    if (sin_t2 > 1.0)
    {
        // Total internal reflection occurs, return the ray with the same direction
        return {intersection_point, this->get_direction()};
    }

    double cos_t = std::sqrt(1.0 - sin_t2);
    vector3 refracted_direction = (incident_ray * (n1 / n2) + normal * (cos_t - cos_i * (n1 / n2))).normalize();

    return {intersection_point + refracted_direction * 0.001, refracted_direction};
}
