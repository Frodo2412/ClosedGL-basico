#pragma once

#include "transformation.h"

class perspective final : public transformation
{
public:
    explicit perspective(const float fov, const float aspect_ratio, const float near, const float far);
};
