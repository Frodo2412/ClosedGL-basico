#include "projection_pipeline.h"

#include <iostream>

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
        std::vector<vector2> points;
        for (const auto& point3 : volume->get_vertexes())
        {
            std::cout << "1. Proyecting vertex: " << point3.x << ", " << point3.y << ", " << point3.z << "\n";
            const auto projected_point = perspective_.transform({point3.x, point3.y, point3.z, 1});
            std::cout << "2. Got transformed point: " << projected_point.get_x() << ", " << projected_point.get_y() <<
                ", " << projected_point.get_z() << ", " << projected_point.get_w() << "\n";

            points.emplace_back(projected_point.get_x() / projected_point.get_w(),
                                projected_point.get_y() / projected_point.get_w());
            std::cout << "3. Pushed point " << points.back().x << ", " << points.back().y << "\n";
        }

        shapes.emplace_back(points, volume->get_color());
    }

    return projection(shapes);
}
