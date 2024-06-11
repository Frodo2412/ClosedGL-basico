#pragma once
#include <vector>

#include "object.h"

class mesh : public object
{
    std::vector<vector3> vertices_;
    std::vector<unsigned int> indices_;

public:
    mesh(const std::vector<vector3>& vertices, const std::vector<unsigned int>& indices, color color,
         double reflectivity, double shininess, double transparency, double refractive_index)
        : object(vertices[0], color, reflectivity, shininess, transparency, refractive_index), vertices_(vertices),
          indices_(indices)
    {
    }

    bool test_intersection(ray& rayo, vector3& point, vector3& normal) override;
    static mesh create_rectangular_prism(const vector3& origin, double width, double height, double depth,
                                         const color& color, double reflectivity, double shininess, float transparency,
                                         float refractive_index
    );

private:
    bool intersect_triangle(const vector3& v0, const vector3& v1, const vector3& v2, ray& rayo, vector3& point,
                            vector3& normal);
};
