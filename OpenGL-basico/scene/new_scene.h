#pragma once

#include "camera.h"
#include "../ray-tracing/object.h"
#include "../graphics/image.h"
#include "../ray-tracing/light.h"
#include "SDL.h"

class new_scene
{
    color background_color_, ambient_;
    double near_, far_;
    int width_, height_;
    camera* camera_;
    std::vector<object*> objects_;
    std::vector<light*> lights_;
    image normal_;
    image reflectivity_;
    image refractivity_;
    int iteraciones_ = 0;
    bool finished_ = false;

    bool cast_ray(ray& cast_ray,
                  const object* this_object,
                  object*& closest_object,
                  vector3& new_intersection_point,
                  vector3& new_intersection_normal) const;

    static int max_depth_;

public:
    new_scene(const char* filename);
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
    color calculate_color(ray& rayo, vector3 intersection_point, vector3 intersection_normal, object* nearest_obj,
                          int level);
    color whitted_ray_tracing(ray& rayo, double& aux_reflectividad, double& aux_refractividad, int level);
    color calculate_diffuse(ray& camera_ray, const vector3& intersection_point, const vector3& intersection_normal, const object* nearest_obj,
                            light* light) const;
    color calculate_specular(ray& rayo, const vector3& intersection_point, const vector3& intersection_normal, const object* nearest_obj, light*
                             light);
    color calculate_reflection(const ray& rayo, vector3 intersection_point, vector3 intersection_normal,
                               object* nearest_obj, int level);
    color calculate_translucency(ray& rayo, vector3 intersection_point, vector3 intersection_normal,
                                 object* nearest_obj, int level);
    color calculate_diffuse_specular(ray& rayo, vector3 intersection_point, vector3 intersection_normal,
                                     object* nearest_obj);
};
