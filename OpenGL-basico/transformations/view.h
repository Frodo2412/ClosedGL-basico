#pragma once
#include "transformation.h"
#include "../scene/camera.h"

class view final : public transformation
{
public:
    explicit view(const camera& camera);
};
