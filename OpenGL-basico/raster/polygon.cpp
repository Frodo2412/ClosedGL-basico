#include "polygon.h"

#include <iostream>

std::vector<line> polygon::get_lines() const
{
    // vertices {100,100}, {200,200}, {300,100}
    auto lines = std::vector<line>();

    for (unsigned int i = 0; i < vertices.size() - 1; i++) lines.emplace_back(vertices[i], vertices[i + 1]);

    lines.emplace_back(vertices[vertices.size() - 1], vertices[0]);

    std::cout << "Lines: " << lines.size() << "\n";

    return lines;
}

polygon::polygon(std::vector<vector2> vertices, const color fill_color): vertices(std::move(vertices)),
                                                                         fill_color(fill_color)
{
}
