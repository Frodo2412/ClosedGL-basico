#include "new_scene.h"
#include <vector>
#include <string>
#include "../ray-tracing/plane.h"
#include "../xml/tinyxml2.h"
#include "../xml/scene_parser.h"

int new_scene::max_depth_ = 100;

bool new_scene::cast_ray(ray& cast_ray,
                         const object* this_object,
                         object*& closest_object,
                         vector3& new_intersection_point,
                         vector3& new_intersection_normal) const
{
    double min_dist = 1e6;
    bool intersection_found = false;

    for (const auto& current_object : objects_)
    {
        if (current_object != this_object)
        {
            vector3 intersection_point, intersection_normal;
            bool valid_int = current_object->test_intersection(cast_ray, intersection_point, intersection_normal);

            if (valid_int)
            {
                double dist = (intersection_point - cast_ray.get_origin()).get_norm();

                if (dist < min_dist)
                {
                    min_dist = dist;
                    closest_object = current_object;
                    new_intersection_point = intersection_point;
                    new_intersection_normal = intersection_normal;
                    intersection_found = true;
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
    try
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

        std::cout << "Scene loaded" << '\n' << "- Shapes: " << objects_.size() << '\n' << "- Lights: " << lights_.size()
            <<
            '\n';
    }
    catch (std::exception& e)
    {
        std::cerr << "Error loading scene: " << e.what() << '\n';
    }
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
        int n = 2; // Número de celdas por lado, para un total de n*n rayos por píxel
        double cell_size = 1.0 / (double)n;

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

    color final_color = (ambient_ + diffuse_specular_color) * (1 - nearest_obj->get_reflectivity())
        + reflection_color * nearest_obj->get_reflectivity();
    final_color = final_color + translucent_color * nearest_obj->get_translucency();
    return final_color;
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

color new_scene::calculate_diffuse(ray& camera_ray, const vector3& intersection_point,
                                   const vector3& intersection_normal,
                                   const object* nearest_obj, light* light) const
{
    color calc_color = {0, 0, 0};

    const vector3 light_direction = (light->get_position() - intersection_point).normalize();
    ray shadow_ray(intersection_point + light_direction * 0.001, light_direction); // Avoid self-intersection

    const double prod = intersection_normal.dot_product(light_direction);

    if (prod <= 0.0) // Solo considerar si la luz incide en la superficie
    {
        return calc_color;
    }

    double light_attenuation = 1.0; // Atenuación de la luz
    color light_color_attenuation = {0, 0, 0}; // Atenuación por color de la luz

    object* closest_object = nullptr;
    vector3 new_intersection_point, new_intersection_normal;

    while (cast_ray(shadow_ray, nearest_obj, closest_object, new_intersection_point, new_intersection_normal))
    {
        const double intersection_distance = (new_intersection_point - intersection_point).get_norm();
        const double light_distance = (light->get_position() - intersection_point).get_norm();
        if (closest_object->get_translucency() < 1.0)
        {
            if (intersection_distance < light_distance)
            {
                if (closest_object->get_translucency() > 0.0)
                {
                    light_attenuation *= closest_object->get_translucency();
                    light_color_attenuation = light_color_attenuation.combine(closest_object->get_color(),
                                                                              closest_object->get_translucency());
                    // Continuar el rayo de sombra
                    shadow_ray = ray(new_intersection_point + light_direction * 0.001, light_direction);
                }
                else
                {
                    // El objeto es opaco, bloquear la luz completamente
                    return calc_color;
                }
            }
            else
            {
                break;
            }
        }
        else
        {
            shadow_ray = ray(new_intersection_point + light_direction * 0.001, light_direction);
        }
    }

    const double intensity = prod * light->get_intensity();

    // Calcular color difuso y especular si no está en la sombra completa
    calc_color = nearest_obj->get_color().combine(light_color_attenuation, light_attenuation) * intensity;

    // Añadir el color calculado al color difuso
    return calc_color;
}

color new_scene::calculate_specular(ray& rayo, const vector3& intersection_point,
                                    const vector3& intersection_normal,
                                    const object* nearest_obj, light* light)
{
    vector3 light_direction = (light->get_position() - intersection_point).normalize();
    vector3 view_direction = (rayo.get_origin() - intersection_point).normalize();
    vector3 reflection_direction = (2.0 * intersection_normal.dot_product(light_direction) * intersection_normal -
        light_direction).normalize();

    double reflection_view_dot = reflection_direction.dot_product(view_direction);
    if (reflection_view_dot < 0.0) { return {0, 0, 0}; }
    // No specular component if the angle is greater than 90 degrees

    double shininess = nearest_obj->get_shininess();
    double specular_intensity = pow(reflection_view_dot, shininess) * light->get_intensity();

    color specular_color = light->get_color() * specular_intensity;

    return specular_color;
}

color new_scene::calculate_diffuse_specular(ray& rayo, vector3 intersection_point, vector3 intersection_normal,
                                            object* nearest_obj)
{
    color diffuse_color = {0, 0, 0};
    color specular_color = {0, 0, 0};

    for (light* light : lights_)
    {
        diffuse_color = diffuse_color + calculate_diffuse(rayo, intersection_point, intersection_normal,
                                                          nearest_obj, light);
        if (nearest_obj->get_shininess() > 0.0)
        {
            specular_color = specular_color + calculate_specular(rayo, intersection_point, intersection_normal,
                                                                 nearest_obj, light);
        }
    }

    return diffuse_color + specular_color;
}

color new_scene::calculate_reflection(const ray& rayo, vector3 intersection_point, vector3 intersection_normal,
                                      object* nearest_obj, int level)
{
    if (level == 0 || nearest_obj->get_reflectivity() <= 0.0) { return {0, 0, 0}; }

    ray reflected_ray = rayo.reflect(intersection_point, intersection_normal);
    double trash1, trash2;
    return whitted_ray_tracing(reflected_ray, trash1, trash2, level - 1);
}

color new_scene::calculate_translucency(ray& rayo, vector3 intersection_point, vector3 intersection_normal,
                                        object* nearest_obj, int level)
{
    color translucency_color = {0, 0, 0};

    if (nearest_obj->get_translucency() > 0.0)
    {
        vector3 rayo_vista = rayo.get_ray_vector().normalize();
        vector3 normal = intersection_normal.normalize();

        double n1, n2; // Índices de refracción
        double cos_theta1 = (-rayo_vista).dot_product(normal);

        if (cos_theta1 > 0.0) 
        {
            // El rayo está pasando del exterior al interior del objeto
            n1 = 1.0; // Índice de refracción del aire
            n2 = nearest_obj->get_refractive_index(); // Índice de refracción del objeto
        } 
        else 
        {
            // El rayo está pasando del interior al exterior del objeto
            n1 = nearest_obj->get_refractive_index(); // Índice de refracción del objeto
            n2 = 1.0; // Índice de refracción del aire
            normal = -normal; // Invertimos la normal para calcular correctamente
            cos_theta1 = -cos_theta1;
        }

        double ratio = n1 / n2;
        double sen_theta1 = sqrt(1 - pow(cos_theta1, 2));
        double sen_theta2 = ratio * sen_theta1;

        if (sen_theta2 <= 1.0) // No hay reflexión interna total
        {
            double cos_theta2 = sqrt(1 - pow(sen_theta2, 2));
            vector3 rayo_t = ratio * rayo_vista + (ratio * cos_theta1 - cos_theta2) * normal;
            ray rayo_refractado = ray(intersection_point + rayo_t.normalize() * 0.0001, rayo_t.normalize());
            double trash1, trash2;
            translucency_color = whitted_ray_tracing(rayo_refractado, trash1, trash2, level - 1);
        }
    }
    return translucency_color;
}
