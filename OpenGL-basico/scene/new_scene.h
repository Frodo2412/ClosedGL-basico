#pragma once

#include "camera.h"
#include "../ray-tracing/object.h"
#include "../graphics/image.h"
#include "../ray-tracing/light.h"

class new_scene
{
    color background_color_;
    float near_, far_;
    int width_, height_;
    camera* camera_;
    std::vector<object*> objects_;
    std::vector<light*> lights_;
public:
    new_scene(int width, int height);
    image Render();
    int get_width();
    int get_height();
    float get_far();
    float get_near();
    color get_background_color();
    color whitted_ray_tracing(ray& rayo);
    color calculate_diffuse(vector3 intersection_point, vector3 intersection_normal, object* nearest_obj);
};
