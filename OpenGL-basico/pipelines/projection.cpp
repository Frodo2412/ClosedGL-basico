#include "projection.h"

#include <utility>

projection::projection(std::vector<polygon> shapes): shapes(std::move(shapes))
{
}
