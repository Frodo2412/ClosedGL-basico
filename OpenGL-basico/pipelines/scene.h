#pragma once

#include <utility>
#include <vector>

#include "../solids/volume.h"

class scene
{
    std::vector<volume*> volumes_;

public:
    explicit scene(std::vector<volume*> volumes) : volumes_(std::move(volumes))
    {
    }

    std::vector<volume*> get_volumes();
};
