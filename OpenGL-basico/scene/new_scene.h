#pragma once

#include "camera.h"
#include "../ray-tracing/object.h"
#include "../graphics/image.h"
#include "../ray-tracing/light.h"

class new_scene
{
    static color ambient_color_;

    color background_color_;
    double near_, far_;
    int width_, height_;
    camera* camera_;
    std::vector<object*> objects_;
    std::vector<light*> lights_;

    bool cast_ray(ray& cast_ray,
                  object*& this_object,
                  object*& closest_object,
                  vector3& new_intersection_point,
                  vector3& new_intersection_normal) const;

    static int max_depth_;

public:
    new_scene(const char* filename);
    std::vector<image> Render();
    int get_width();
    int get_height();
    double get_far();
    double get_near();
    color get_background_color();
    color calculate_color(ray& rayo, vector3 intersection_point, vector3 intersection_normal, object* nearest_obj, int level);
    color whitted_ray_tracing(ray& rayo, double& aux_reflectividad, double& aux_refractividad, int level);
    color calculate_reflection(const ray& rayo, vector3 intersection_point, vector3 intersection_normal,
                               object* nearest_obj, int level);
    color calculate_translucency(const ray& rayo, vector3 intersection_point, vector3 intersection_normal,
                                 object* nearest_obj);
    color calculate_diffuse_specular(ray& rayo, vector3 intersection_point, vector3 intersection_normal,
                                     object* nearest_obj);
};
