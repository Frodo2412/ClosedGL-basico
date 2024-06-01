#include "viewport_pipeline.h"

projection viewport_pipeline::get_viewport_coordinates(const projection& ndc_projection) const
{
    std::vector<polygon> shapes;

    for (const auto& polygon : ndc_projection.shapes)
    {
        std::vector<line> edges;
        for (const auto edge : polygon.edges)
        {
            const auto start = edge.get_start();
            const auto end = edge.get_end();

            const auto projected_start = viewport_.transform(start);
            const auto projected_end = viewport_.transform(end);

            edges.emplace_back(vector2(projected_start.get_x(), projected_start.get_y()),
                               vector2(projected_end.get_x(), projected_end.get_y()));
        }

        shapes.emplace_back(edges, polygon.fill_color);
    }

    return projection(shapes);
}
