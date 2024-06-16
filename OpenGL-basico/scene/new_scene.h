#pragma once

#include "camera.h"
#include "../ray-tracing/object.h"
#include "../graphics/image.h"
#include "../ray-tracing/light.h"
#include "SDL.h"

class new_scene
{
    static color ambient_color_;

    color background_color_;
    double near_, far_;
    int width_, height_;
    camera* camera_;
    std::vector<object*> objects_;
    std::vector<light*> lights_;
    image normal_ = image::create_empty_image(width_, height_, normal);
    image reflectivity_ = image::create_empty_image(width_, height_, reflectividad);
    image refractivity_ = image::create_empty_image(width_, height_, refractividad);
    int iteraciones_ = 0;
    bool finished_ = false;

    bool cast_ray(ray& cast_ray,
                  object*& this_object,
                  object*& closest_object,
                  vector3& new_intersection_point,
                  vector3& new_intersection_normal) const;

public:
    new_scene(int width, int height, const char* filename);
    void Render(SDL_Renderer* renderer, int progress);
    bool is_finished();
    image get_normal_image();
    image get_reflectivity_image();
    image get_refractivity_image();
    int get_iter();
    int get_width();
    int get_height();
    double get_far();
    double get_near();
    color get_background_color();
    color calculate_color(ray& rayo, vector3 intersection_point, vector3 intersection_normal, object* nearest_obj);
    color whitted_ray_tracing(ray& rayo, double& aux_reflectividad, double& aux_refractividad);
    color calculate_reflection(const ray& rayo, vector3 intersection_point, vector3 intersection_normal,
                               object* nearest_obj);
    color calculate_translucency(const ray& rayo, vector3 intersection_point, vector3 intersection_normal,
                                 object* nearest_obj);
    color calculate_diffuse_specular(ray& rayo, vector3 intersection_point, vector3 intersection_normal,
                                     object* nearest_obj);
};
