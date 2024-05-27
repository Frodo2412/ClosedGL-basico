#include "projection.h"

#include <utility>

projection::projection(const int width, const int height, std::vector<polygon> shapes): width(width), height(height),
    shapes(
        std::move(shapes))
{
}
