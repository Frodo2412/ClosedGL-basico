#pragma once
#include <vector>

#include "polygon.h"

struct projection
{
    int width, height;
    std::vector<polygon> shapes;

    explicit projection(int width, int height, std::vector<polygon> shapes);
};
