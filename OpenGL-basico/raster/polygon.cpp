#include "polygon.h"

#include <iostream>

polygon::polygon(std::vector<line> edges, const color fill_color): edges(std::move(edges)), fill_color(fill_color)
{
}
