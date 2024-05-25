#pragma once
#include <cmath>

#include "transformation.h"

class perspective final : public transformation
{
public:
    explicit perspective(const float fov, const float aspect, const float near, const float far);
};
