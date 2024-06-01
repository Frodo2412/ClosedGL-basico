#pragma once

#include "volume.h"
#include "../geometry/vector3.h"

enum operation { and, or, not };

class solid final : public volume
{
    volume *right_hs_, *left_hs_;
    operation operation_;

public:
    bool contains(vector3 point) const override;
    std::vector<polygon> get_faces() const override;
};
