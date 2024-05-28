#pragma once
#include <cmath>
#include "../scene/scene.h"
#include "transformation.h"

class perspective final : public transformation
{
public:
    explicit perspective(scene * scene);
};
