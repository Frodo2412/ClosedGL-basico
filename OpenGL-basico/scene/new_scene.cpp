#include "new_scene.h"
#include <vector>
#include <string>
#include "../ray-tracing/plane.h"
#include "../xml/tinyxml2.h"
#include "../xml/scene_parser.h"

int new_scene::max_depth_ = 10;

bool new_scene::cast_ray(ray& cast_ray,
                         const object* this_object,
                         object*& closest_object,
                         vector3& new_intersection_point,
                         vector3& new_intersection_normal) const
{
    vector3 intersection_point, intersection_normal;
    double min_dist = 1e6;
    bool intersection_found = false;
    for (const auto current_object : objects_)
    {
        if (current_object != this_object)
        {
            const bool valid_int = current_object->test_intersection(cast_ray,
                                                                     intersection_point,
                                                                     intersection_normal);

            if (valid_int)
            {
                intersection_found = true;

                const double dist = (intersection_point - cast_ray.get_origin()).get_norm();

                if (dist < min_dist)
                {
                    min_dist = dist;
                    closest_object = current_object;
                    new_intersection_point = intersection_point;
                    new_intersection_normal = intersection_normal;
                }
            }
        }
    }

    return intersection_found;
}

new_scene::new_scene(const char* filename) : normal_(0, 0, std::vector<pixel>(), normal),
                                             reflectivity_(0, 0, std::vector<pixel>(), reflectividad),
                                             refractivity_(0, 0, std::vector<pixel>(), refractividad)
{
    near_ = 0.1;
    far_ = 1000;

    tinyxml2::XMLDocument doc;
    auto res = doc.LoadFile(filename);
    if (res != tinyxml2::XML_SUCCESS)
    {
        throw std::runtime_error("Failed to load file " + std::string(filename) + ": " + std::to_string(res));
    }

    tinyxml2::XMLPrinter printer;
    doc.Print(&printer);

    auto dom_scene = doc.FirstChildElement("document")->FirstChildElement("scene");
    if (!dom_scene)
    {
        throw std::runtime_error("'scene' element not found");
    }

    width_ = scene_parser::parse_int(dom_scene, "width");
    height_ = scene_parser::parse_int(dom_scene, "height");

    normal_ = image::create_empty_image(width_, height_, normal);
    reflectivity_ = image::create_empty_image(width_, height_, reflectividad);
    refractivity_ = image::create_empty_image(width_, height_, refractividad);

    if (dom_scene->NoChildren())
    {
        throw std::runtime_error("No objects found in scene");
    }

    tinyxml2::XMLNode* node = dom_scene->FirstChild();
    do
    {
        const auto element = node->ToElement();

        const auto element_type = std::string(element->Name());

        if (element_type == "shape") { objects_.push_back(scene_parser::parse_object(element)); }
        else if (element_type == "light") { lights_.push_back(scene_parser::parse_light(element)); }
        else if (element_type == "camera") { camera_ = scene_parser::parse_camera(element, width_, height_); }
        else if (element_type == "background") { background_color_ = scene_parser::parse_color(element); }
        else if (element_type == "ambient") { ambient_ = scene_parser::parse_color(element); }
        else { throw std::runtime_error("Unknown element type: " + element_type); }

        node = node->NextSibling();
    }
    while (node != nullptr);

    std::cout << "Scene loaded" << '\n' << "- Shapes: " << objects_.size() << '\n' << "- Lights: " << lights_.size() <<
        '\n';
}

void new_scene::Render(SDL_Renderer* renderer, int progress)
{
    if (iteraciones_ >= width_)
    {
        finished_ = true;
    }
    if (!finished_)
    {
        /* Creamos el rayo que sale de la camara, el cual usaremos para el trazado de rayos */
        ray rayo = ray(camera_->get_position(), {0, 0, 0});

        double x_factor = 2.0 / (double)width_;
        double y_factor = 2.0 / (double)height_;
        int n = 5; // Número de celdas por lado, para un total de n*n rayos por píxel
        double cell_size = 1.0 / (double)n;
        std::cout << "Rendering..." << std::endl;

        /* Calculamos todos los píxeles */

        int x = iteraciones_; // el pixel siguiente a donde me quedé la última vez. 
        int fin;
        if (x + progress > width_)
        {
            fin = width_;
        }
        else
        {
            fin = x + progress;
        }
        for (x; x < fin; x++)
        {
            for (int y = 0; y < height_; y++)
            {
                color final_color = {0, 0, 0}; // Color inicial del píxel
                double final_reflectividad = 0.0;
                // => En estas variables cargaremos el valor de los coeficientes de reflexion y refraccion en el pixel x, y
                double final_refractividad = 0.0;
                /* Para cada celda dentro del píxel */
                for (int i = 0; i < n; ++i)
                {
                    for (int j = 0; j < n; ++j)
                    {
                        // Desplazamiento dentro del píxel
                        double sample_x = (double)x + (i + 0.5) * cell_size;
                        double sample_y = (double)y + (j + 0.5) * cell_size;

                        // Normalizamos el pixel por el que pasará el rayo
                        double norm_x = sample_x * x_factor - 1.0;
                        double norm_y = sample_y * y_factor - 1.0;

                        // Casteamos el rayo para que pase por el píxel normalizado (x, y)
                        camera_->generate_ray(norm_x, norm_y, rayo);

                        double aux_reflectividad = 0.0;
                        double aux_refractividad = 0.0;

                        // Calculamos el color del rayo
                        color sample_color =
                            whitted_ray_tracing(rayo, aux_reflectividad, aux_refractividad, max_depth_);

                        // Sumamos el color de la muestra al color final del píxel
                        final_color += sample_color;
                        final_reflectividad += aux_reflectividad;
                        final_refractividad += aux_refractividad;
                    }
                }
                iteraciones_ = x + 1;

                // Promediamos el color final dividiendo por el número de muestras
                final_color = final_color / (n * n);
                final_reflectividad = final_reflectividad / (n * n);
                final_refractividad = final_refractividad / (n * n);

                // Guardamos el píxel con el color final calculado
                pixel px = pixel(x, y, final_color);
                pixel px_reflectividad = pixel(x, y, color(255 * final_reflectividad, 255 * final_reflectividad,
                                                           255 * final_reflectividad));
                pixel px_refractividad = pixel(x, y, color(255 * final_refractividad, 255 * final_refractividad,
                                                           255 * final_refractividad));
                normal_.pixels.push_back(px);
                reflectivity_.pixels.push_back(px_reflectividad);
                refractivity_.pixels.push_back(px_refractividad);
            }
        }
    }
}

bool new_scene::is_finished()
{
    return finished_;
}

image new_scene::get_normal_image()
{
    return normal_;
}

image new_scene::get_reflectivity_image()
{
    return reflectivity_;
}

image new_scene::get_refractivity_image()
{
    return refractivity_;
}

int new_scene::get_iter()
{
    return iteraciones_;
}

int new_scene::get_width()
{
    return width_;
}

int new_scene::get_height()
{
    return height_;
}

double new_scene::get_far()
{
    return far_;
}

double new_scene::get_near()
{
    return near_;
}

color new_scene::get_background_color()
{
    return background_color_;
}

color new_scene::calculate_color(ray& rayo, vector3 intersection_point, vector3 intersection_normal,
                                 object* nearest_obj, int level)
{
    if (level == 0) { return {0, 0, 0}; }

    const color diffuse_specular_color = calculate_diffuse_specular(rayo, intersection_point, intersection_normal,
                                                                    nearest_obj);
    color reflection_color = {0, 0, 0};
    color translucent_color = {0, 0, 0};
    if (nearest_obj->get_reflectivity() > 0.0)
    {
        reflection_color = calculate_reflection(rayo, intersection_point, intersection_normal, nearest_obj, level - 1);
    }
    if (nearest_obj->get_translucency() > 0.0)
    {
        translucent_color = calculate_translucency(rayo, intersection_point, intersection_normal, nearest_obj,
                                                   level - 1);
    }

    color mat_color = ambient_;
    mat_color += reflection_color * nearest_obj->get_reflectivity() + diffuse_specular_color * (1 - nearest_obj->
        get_reflectivity());
    mat_color += translucent_color * nearest_obj->get_translucency() + mat_color * (1 - nearest_obj->
        get_translucency());

    return mat_color / 3;
}

color new_scene::whitted_ray_tracing(ray& rayo, double& aux_reflectividad, double& aux_refractividad, int level)
{
    if (level == 0) { return {0, 0, 0}; }

    object* nearest_obj = nullptr;
    vector3 intersection_point = {0, 0, 0}; //=> Variable en la que cargaremos el punto de interseccion con los objetos
    vector3 intersection_normal = {0, 0, 0};
    //=> Variable en la que cargaremos la normal del objeto en el punto de interseccion

    color px_color = get_background_color(); //=> Variable en la que cargaremos el color del pixel

    cast_ray(rayo, nullptr, nearest_obj, intersection_point, intersection_normal);

    aux_reflectividad = 0.0;
    aux_refractividad = 0.0;
    /* Calcularemos cuanta luz recibe el punto de interseccion */
    if (nearest_obj != nullptr)
    {
        px_color = calculate_color(rayo, intersection_point, intersection_normal, nearest_obj, level - 1);
        aux_reflectividad = nearest_obj->get_reflectivity();
        aux_refractividad = 1 / nearest_obj->get_refractive_index();
    }
    return px_color;
}

color new_scene::calculate_diffuse(ray& rayo, vector3 intersection_point, vector3 intersection_normal,
                                   object* nearest_obj, light* light, double& intensity)
{
    intensity = 0.0;

    vector3 light_direction = (light->get_position() - intersection_point).normalize();
    ray shadow_ray(intersection_point + light_direction * 0.001, light_direction);

    const double prod = intersection_normal.dot_product(light_direction);

    if (prod < 0.0) { return {0, 0, 0}; }
    intensity = prod * light->get_intensity();

    object* closest_object;
    vector3 new_intersection_point, new_intersection_normal;
    if (cast_ray(shadow_ray, nearest_obj, closest_object, new_intersection_point, new_intersection_normal))
    {
        const double intersection_distance = (new_intersection_point - intersection_point).get_norm();
        const double light_distance = (light->get_position() - intersection_point).get_norm();

        if (intersection_distance > light_distance)
        {
            // El objeto que genera sombras esta mas lejos que la luz
            return nearest_obj->get_color() * intensity;
        }
        //
        // // Tengo sombra
        // intensity = std::max(0.0, intensity - (1 - closest_object->get_translucency()));
        // const color material_color = nearest_obj->get_color() * intensity;
        // return material_color;
        return closest_object->get_color() * closest_object->get_translucency();
    }
    // No hay objetos entre yo y la luz
    return nearest_obj->get_color() * intensity;
}

color new_scene::calculate_diffuse_specular(ray& rayo, vector3 intersection_point, vector3 intersection_normal,
                                            object* nearest_obj)
{
    color final_color = background_color_;
    color diffuse_color = {0, 0, 0};
    color specular_color = {0, 0, 0};

    double shininess = nearest_obj->get_shininess();
    for (light* luz : lights_)
    {
        double light_intensity = 0.0;
        diffuse_color = diffuse_color + calculate_diffuse(rayo, intersection_point, intersection_normal, nearest_obj,
                                                          luz, light_intensity);

        // Calculo de luz especular si el objeto tiene brillo
        if (shininess > 0.0)
        {
            if (light_intensity > 0.05)
            {
                vector3 rayo_s = (luz->get_position() - intersection_point).normalize();
                ray sombra(intersection_point + (rayo_s * 0.0001), rayo_s); // Crear un rayo hacia la luz
                vector3 light_ray = sombra.get_ray_vector().normalize();
                vector3 reflection_vector = (light_ray - (intersection_normal * 2 * light_ray.dot_product(
                    intersection_normal))).normalize();
                vector3 camera_vector = -rayo.get_ray_vector().normalize();
                double prod = reflection_vector.dot_product(camera_vector);
                if (prod > 0.0f)
                {
                    double specular_intensity = pow(prod, shininess);
                    specular_color = specular_color + (luz->get_color() * specular_intensity);
                }
            }
        }
    }

    final_color = final_color + diffuse_color + specular_color;
    final_color = final_color + diffuse_color + specular_color;
    return final_color;
}

color new_scene::calculate_reflection(const ray& rayo, vector3 intersection_point, vector3 intersection_normal,
                                      object* nearest_obj, int level)
{
    color translucency_color = {0, 0, 0};

    if (level == 0) { return translucency_color; }

    try
    {
        if (nearest_obj->get_reflectivity() > 0.0)
        {
            vector3 view_dir = rayo.get_ray_vector();
            vector3 normal = intersection_normal;
            vector3 reflected_dir = (view_dir - (normal * 2 * view_dir.dot_product(normal)));

            ray reflected_ray(intersection_point + reflected_dir * 0.00001, reflected_dir);

            double trash1, trash2;
            translucency_color = whitted_ray_tracing(reflected_ray, trash1, trash2, level - 1);
        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return translucency_color;
}

color new_scene::calculate_translucency(const ray& rayo, vector3 intersection_point, vector3 intersection_normal,
                                        object* nearest_obj, int level)
{
    color translucency_color = {0, 0, 0};
    try
    {
        if (nearest_obj->get_translucency() > 0.0)
        {
            vector3 p = rayo.get_ray_vector().normalize(), n = intersection_normal;
            double r = 1.0 / nearest_obj->get_refractive_index(), c = -n.dot_product(p);

            if (c < 0.0)
            {
                n = n * -1;
                c = n.dot_product(p);
            }


            const auto r_2 = 1 - pow(r, 2);
            const auto c_2 = 1 - pow(c, 2);
            const auto root = r_2 * c_2;

            if (root < 0.0)
            {
                std::cout << root << '\n';
                throw std::exception("Trying to take root of negative number");
            }

            const vector3 refracted = p * r + n * (r * c - sqrt(root));
            ray refracted_ray(intersection_point + refracted * 0.01, intersection_point + refracted);

            // Chequeo por otras intersecciones con el mismo objeto

            object* closest_object;
            vector3 new_intersection_point, new_intersection_normal;
            bool test = nearest_obj->test_intersection(refracted_ray, new_intersection_point, new_intersection_normal);
            bool intersection_found = false;
            ray final_ray;
            if (test)
            {
                vector3 p2 = refracted_ray.get_ray_vector().normalize(), n2 = new_intersection_normal;
                double r2 = nearest_obj->get_refractive_index(), c2 = -n2.dot_product(p2);

                if (c < 0.0)
                {
                    n2 = n2 * -1;
                    c2 = n2.dot_product(p2);
                }

                vector3 refracted2 = p2 * r2 + n2 * (r2 * c2 - sqrt(1 - pow(r2, 2) * 1 - pow(c2, 2)));
                ray refracted_ray2(new_intersection_point + refracted2 * 0.01, new_intersection_point + refracted2);

                intersection_found = cast_ray(refracted_ray,
                                              nearest_obj,
                                              closest_object,
                                              new_intersection_point,
                                              new_intersection_normal);
                final_ray = refracted_ray2;
            }
            else
            {
                intersection_found = cast_ray(refracted_ray,
                                              nearest_obj,
                                              closest_object,
                                              new_intersection_point,
                                              new_intersection_normal);
                final_ray = refracted_ray;
            }

            // Aca calculo el color de nearest_obj
            color color;
            if (intersection_found)
            {
                if (closest_object->has_material())
                {
                    auto aux_reflectividad = 0.0;
                    auto aux_refractividad = 0.0;
                    color = whitted_ray_tracing(final_ray, aux_reflectividad, aux_refractividad, level - 1);
                }
                else
                {
                    color = calculate_diffuse_specular(final_ray, new_intersection_point, new_intersection_normal,
                                                       closest_object);
                }
            }

            translucency_color = color;
        }
    }
    catch (std::exception& e)
    {
        ray reflected_ray(intersection_point + rayo.get_ray_vector() * 0.00001, rayo.get_ray_vector());
        double trash1, trash2;
        translucency_color = whitted_ray_tracing(reflected_ray, trash1, trash2, level - 1);
    }


    return translucency_color;
}
