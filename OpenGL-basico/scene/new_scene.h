#pragma once

#include "camera.h"
#include "../ray-tracing/sphere.h"
#include "../pipelines/image.h"

class new_scene
{
    int width_, height_;
    camera* camera_;
    sphere* sphere_;
public:
    new_scene(int width, int height);
    image Render();
    int get_width();
    int get_height();
};
