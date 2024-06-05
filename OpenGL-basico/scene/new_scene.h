#pragma once

#include "camera.h"
#include "../ray-tracing/object.h"
#include "../graphics/image.h"
#include "../ray-tracing/light.h"

class new_scene
{
    int width_, height_;
    camera* camera_;
    std::vector<object*> objects_;
    std::vector<light*> lights_;
public:
    new_scene(int width, int height);
    image Render();
    int get_width();
    int get_height();
    color sombra_RR(object* obj, vector3& intersection_point, vector3& normal);
};
