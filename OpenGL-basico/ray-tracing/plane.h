#pragma once

#include "object.h"

class plane : public object
{
    vector3 normal_;
    float A_, B_, C_, D_;
public:
    plane(vector3 pos, vector3 normal, color color) : object(pos, color), normal_(normal)
    {
        A_ = normal_.x;
        B_ = normal_.y;
        C_ = normal_.z;
        D_ = -(pos.x * A_ + pos.y * B_ + pos.z * C_);
    }

    bool test_intersection(ray& rayo, vector3& point, vector3& normal, color& color) override;
    ~plane() override;
};
