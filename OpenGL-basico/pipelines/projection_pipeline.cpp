#include "projection_pipeline.h"

#include <iostream>

#include "../raster/point.h"
#include "../raster/polygon.h"
#include "../transformations/perspective.h"

projection_pipeline::projection_pipeline(const float fov, const float aspect, const float near, const float far):
    perspective_(perspective(fov, aspect, near, far))
{
}

projection projection_pipeline::project(scene scene) const
{
    std::vector<polygon> shapes;

    for (const auto& volume : scene.get_volumes())
    {
        std::cout << "Proyecting volume: " << volume->get_position().x << ", " << volume->get_position().y << ", " <<
            volume->get_position().z << "\n";
        std::vector<line> edges;
        for (const auto& edge : volume->get_edges())
        {
            const auto start = edge.get_start();
            const auto end = edge.get_end();

            const auto projected_start = perspective_.transform({start.x, start.y, start.z, 1});
            const auto projected_end = perspective_.transform({end.x, end.y, end.z, 1});

            edges.emplace_back(vector2(
                                   projected_start.get_x() / projected_start.get_w(),
                                   projected_start.get_y() / projected_start.get_w()),
                               vector2(
                                   projected_end.get_x() / projected_end.get_w(),
                                   projected_end.get_y() / projected_end.get_w()));
        }

        shapes.emplace_back(edges, volume->get_color());
    }

    return projection(shapes);
}
