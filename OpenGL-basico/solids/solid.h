#pragma once

#include "volume.h"

enum operation { and, or, not };

class solid final : public volume
{
    volume *right_hs_, *left_hs_;
    operation operation_;

public:
    bool contains(point3 point) const override;
};
