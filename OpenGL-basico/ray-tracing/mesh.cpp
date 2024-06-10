#include "mesh.h"

bool mesh::intersect_triangle(const vector3& v0, const vector3& v1, const vector3& v2, ray& rayo, vector3& point, vector3& normal)
{
    // Calcula el vector de la arista 1 y la arista 2 del triángulo
    vector3 edge1 = v1 - v0;
    vector3 edge2 = v2 - v0;

    double EPSILON = 1e-6; // Debido a las limitaciones de precisión de los números flotantes.

    // Calcula el producto cruzado de las aristas para obtener la normal del triángulo
    normal = edge1.cross_product(edge2).normalize();

    // Calcula el determinante
    vector3 h = rayo.get_direction().cross_product(edge2);
    double discriminant = edge1.dot_product(h);

    // el rayo es paralelo al plano del triángulo
    if (discriminant > -EPSILON && discriminant < EPSILON)
        return false;

    double f = 1.0 / discriminant;
    vector3 s = rayo.get_origin() - v0;
    double u = f * s.dot_product(h);

    // Verifica si el punto de intersección está dentro del triángulo
    if (u < 0.0 || u > 1.0)
        return false;

    vector3 q = s.cross_product(edge1);
    double v = f * rayo.get_direction().dot_product(q);

    // Verifica si el punto de intersección está dentro del triángulo
    if (v < 0.0 || u + v > 1.0)
        return false;

    // Calcula t para determinar la distancia desde el origen del rayo al punto de intersección
    double t = f * edge2.dot_product(q);

    // Verifica si t es negativo, lo que significa que el punto de intersección está detrás del origen del rayo
    if (t < EPSILON)
        return false;

    // Calcula el punto de intersección
    point = rayo.get_origin() + rayo.get_direction() * t;

    return true;
}

bool mesh::test_intersection(ray& rayo, vector3& point, vector3& normal)
{
    bool hit = false;
    double closest_t = std::numeric_limits<double>::max(); // La distancia más cercana como un valor grande

    for (size_t i = 0; i < indices_.size(); i += 3) // Iteramos sobre los índices de los triángulos
    {
        const vector3& v0 = vertices_[indices_[i]];
        const vector3& v1 = vertices_[indices_[i + 1]];
        const vector3& v2 = vertices_[indices_[i + 2]];
         
        vector3 temp_point, temp_normal;  // Variables temporales para  el punto y la normal de intersección del triángulo
        
        if (intersect_triangle(v0, v1, v2, rayo, temp_point, temp_normal))
        {
            hit = true;
            double t = (temp_point - rayo.get_origin()).get_length();
            if (t < closest_t) //  Actualiza el punto de intersección, la normal y la distancia a la más cercana encontrada 
            {
                closest_t = t;
                point = temp_point;
                normal = temp_normal;
            }
        }
    }

    return hit;
}

mesh mesh::create_rectangular_prism(const vector3& esq_trasera, double width, double height, double depth, const color& color, double reflectivity, double shininess)
{
    //   v3 ---- v2
    //  /       / |            
    // v7 --- v6  |           z
    // |  v0 --|-v1          |___ x
    // | /     |/           /
    // v4 --- v5           y
    vector3 v0(esq_trasera.get_x(), esq_trasera.get_y(), esq_trasera.get_z());
    vector3 v1(esq_trasera.get_x() + width, esq_trasera.get_y(), esq_trasera.get_z());
    vector3 v2(esq_trasera.get_x() + width, esq_trasera.get_y() + height, esq_trasera.get_z());
    vector3 v3(esq_trasera.get_x(), esq_trasera.get_y() + height, esq_trasera.get_z());
    vector3 v4(esq_trasera.get_x(), esq_trasera.get_y(), esq_trasera.get_z() + depth);
    vector3 v5(esq_trasera.get_x() + width, esq_trasera.get_y(), esq_trasera.get_z() + depth);
    vector3 v6(esq_trasera.get_x() + width, esq_trasera.get_y() + height, esq_trasera.get_z() + depth);
    vector3 v7(esq_trasera.get_x(), esq_trasera.get_y() + height, esq_trasera.get_z() + depth);

    // Creamos la lista de vértices y la lista de índices para los triángulos que forman el prisma rectangular
    std::vector<vector3> vertices = { v0, v1, v2, v3, v4, v5, v6, v7 };
    std::vector<unsigned int> indices = {
        0, 1, 2, 2, 3, 0, // Cara lateral
        1, 5, 6, 6, 2, 1, // Cara lateral
        4, 5, 6, 6, 7, 4, // Cara lateral
        0, 3, 7, 7, 4, 0, // Cara lateral
        0, 1, 5, 5, 4, 0, // Base
        2, 3, 7, 7, 6, 2  // Tapa
    };

    // Creamos y devolvemos la malla del prisma rectangular
    return mesh(vertices, indices, color, reflectivity, shininess);
}
