#pragma once

#include "camera.h"
#include "../ray-tracing/object.h"
#include "../pipelines/image.h"
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
};
