#pragma once

#include "projection.h"
#include "scene.h"
#include "../transformations/perspective.h"

class projection_pipeline
{
    perspective perspective_;

public:
    explicit projection_pipeline(float fov, float aspect, float near, float far);

    projection project(scene scene) const;
};
