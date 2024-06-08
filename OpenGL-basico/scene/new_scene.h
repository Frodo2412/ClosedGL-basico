#pragma once

#include "camera.h"
#include "../ray-tracing/object.h"
#include "../graphics/image.h"
#include "../ray-tracing/light.h"

class new_scene
{
    color background_color_;
    double near_, far_;
    int width_, height_;
    camera* camera_;
    std::vector<object*> objects_;
    std::vector<light*> lights_;

public:
    new_scene(int width, int height, std::vector<object*> objects, std::vector<light*> lights);
    image Render();
    int get_width();
    int get_height();
    double get_far();
    double get_near();
    color get_background_color();
    color whitted_ray_tracing(ray& rayo);
    color calculate_diffuse(vector3 intersection_point, vector3 intersection_normal, object* nearest_obj);
    color calculate_specular(ray& rayo, vector3 interction_point, vector3 intersection_normal, object* nearest_obj);
};
