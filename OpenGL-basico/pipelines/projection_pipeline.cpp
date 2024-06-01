#include "projection_pipeline.h"

#include <iostream>

#include "../raster/line.h"
#include "../raster/polygon.h"
#include "../transformations/perspective.h"

projection_pipeline::projection_pipeline(const float fov, const float aspect, const float near, const float far):
    perspective_(perspective(fov, aspect, near, far))
{
}

projection projection_pipeline::project(scene scene) const
{
    std::cout << "Proyecting scene:\n";

    const auto volumes = scene.get_volumes();
    std::cout << "- Number of volumes: " << volumes.size() << "\n";

    std::vector<polygon> shapes;

    for (const auto& volume : volumes)
    {
        for (const auto& face : volume->get_faces())
        {
            std::vector<line> edges;
            for (const auto& edge : face.edges)
            {
                const auto start = edge.get_start();
                const auto end = edge.get_end();

                const auto projected_start = perspective_.transform({start.x, start.y, start.z, 1});
                const auto projected_end = perspective_.transform({end.x, end.y, end.z, 1});
                edges.emplace_back(vector3(
                                       projected_start.get_x() / projected_start.get_w(),
                                       projected_start.get_y() / projected_start.get_w(),
                                       start.get_z()),
                                   vector3(
                                       projected_end.get_x() / projected_end.get_w(),
                                       projected_end.get_y() / projected_end.get_w(), end.get_z()));
            }
            shapes.emplace_back(edges, volume->get_color());
        }
    }

    std::cout << "- Generated shapes: " << shapes.size() << "\n";

    return projection(shapes);
}
