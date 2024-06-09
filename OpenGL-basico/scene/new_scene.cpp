#include "new_scene.h"
#include <vector>
#include <string>
#include "../ray-tracing/plane.h"
#include "../xml/tinyxml2.h"
#include "../xml/scene_parser.h"


new_scene::new_scene(const int width, const int height, const char* filename) : width_(width), height_(height)
{
    near_ = 0.1;
    far_ = 100;

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
        else { throw std::runtime_error("Unknown element type: " + element_type); }

        node = node->NextSibling();
    }
    while (node != nullptr);

    std::cout << "Scene loaded" << '\n' << "- Shapes: " << objects_.size() << '\n' << "- Lights: " << lights_.size() <<
        '\n';
}

std::vector<image> new_scene::Render()
{
    /* Vector donde cargaremos las 3 imagenes generadas */
    std::vector<image> resultado;
    /* Vector donde se ira guardando el color (luz) acumulado por cada pixel */
    std::vector<pixel> pixels;

    /* Vector donde se ira guardando la relfectividad acumulada por cada pixel */
    std::vector<pixel> reflectividad;

    /* Vector donde se ira guardando la refractividad acumulada por cada pixel */
    std::vector<pixel> refractividad;
    /* Creamos el rayo que sale de la camara, el cual usaremos para el trazado de rayos */
    ray rayo = ray(camera_->get_position(), {0, 0, 0});

    double x_factor = 2.0 / (double)width_;
    double y_factor = 2.0 / (double)height_;
    int n = 2; // Número de celdas por lado, para un total de n*n rayos por píxel
    double cell_size = 1.0 / (double)n;

    /* Calculamos todos los píxeles */
    for(int x = 0 ; x < width_ ; x++)
    {
        for(int y = 0 ; y < height_ ; y++)
        {
            color final_color = {0, 0, 0}; // Color inicial del píxel
            double final_reflectividad = 0.0;// => En estas variables cargaremos el valor de los coeficientes de reflexion y refraccion en el pixel x, y
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
                    color sample_color = whitted_ray_tracing(rayo, aux_reflectividad, aux_refractividad);

                    // Sumamos el color de la muestra al color final del píxel
                    final_color += sample_color;
                    final_reflectividad += aux_reflectividad;
                    final_refractividad += aux_refractividad;
                }
            }

            // Promediamos el color final dividiendo por el número de muestras
            final_color = final_color / (n * n);
            final_reflectividad = final_reflectividad / (n * n);
            final_refractividad = final_refractividad / (n * n);

            // Guardamos el píxel con el color final calculado
            pixel px = pixel(x, y, final_color);
            pixel px_reflectividad = pixel(x, y, color(255 * final_reflectividad, 255 * final_reflectividad, 255 * final_reflectividad));
            pixel px_refractividad = pixel(x, y, color(255 * final_refractividad, 255 * final_refractividad, 255 * final_refractividad));
            pixels.push_back(px);
            reflectividad.push_back(px_reflectividad);
            refractividad.push_back(px_refractividad);
        }
    }
    resultado.push_back(image(width_, height_, pixels, image_type::normal));
    resultado.push_back(image(width_, height_, reflectividad, image_type::reflectividad));
    resultado.push_back(image(width_, height_, refractividad, image_type::refractividad));
    return resultado;
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

color new_scene::whitted_ray_tracing(ray& rayo, double& aux_reflectividad, double& aux_refractividad)
{
    vector3 intersection_point = {0, 0, 0};//=> Variable en la que cargaremos el punto de interseccion con los objetos
    vector3 intersection_normal = {0, 0, 0};//=> Variable en la que cargaremos la normal del objeto en el punto de interseccion

    /* La distancia mas cercana inicialmente es far */
    double z_buffer = get_far();
    
    object* nearest_obj = nullptr;
    
    color px_color = get_background_color();//=> Variable en la que cargaremos el color del pixel

    /* Calcularemos el objeto mas cercano con el que interseca el rayo */
    for(object* obj : objects_)
    {
        /* Para cada objeto en la escena calcularemos si el rayo interseca con este */
        vector3 i_point = {0, 0, 0};
        vector3 i_normal = {0, 0, 0};
        if (obj->test_intersection(rayo, i_point, i_normal))
        {
            double distance = (i_point - camera_->get_position()).get_norm();//=> Distancia entre la camara y el punto de interseccion
            if(distance < get_far() && distance > get_near())// => checkeamos si el punto de interseccion esta en el rango de renderizado
            {
                if(distance < z_buffer) // => si la distancia es menor a la del z-buffer actual, actualizamos el z-buffer
                {
                    /* Guardamos los valores de la interseccion para usarlos a futuro */
                    intersection_point = i_point;
                    intersection_normal = i_normal;
                    nearest_obj = obj;
                    z_buffer = distance;
                }
            }
        }
    }
    aux_reflectividad = 0.0;
    aux_refractividad = 0.0;
    /* Calcularemos cuanta luz recibe el punto de interseccion */
    if(nearest_obj != nullptr)
    {
        color diffuse_color = calculate_diffuse(intersection_point, intersection_normal, nearest_obj);
        color specular_color = calculate_specular(rayo, intersection_point, intersection_normal, nearest_obj);
        px_color = diffuse_color + specular_color;
        aux_reflectividad = nearest_obj->get_reflectivity();
        aux_refractividad = 0.5;// poner aca la refractividad del objeto
    }
    return px_color;
}

color new_scene::calculate_diffuse(vector3 intersection_point, vector3 intersection_normal, object* nearest_obj)
{
    double light_intensity = 0;//=> Variable en la que cargaremos la intensidad de la luz en el punto de interseccion
    color diffuse_color = get_background_color();
    color acum_color = {0, 0, 0};
    for(light* luz : lights_)
    {
        /* Veremos si teniendo en cuenta la luz puntual "Luz" el punto de interseccion esta en sombra o no */
        luz->compute_illumination(intersection_point, intersection_normal, objects_, nearest_obj, light_intensity);
        acum_color = nearest_obj->get_color();
        acum_color.set_red(acum_color.get_red() * light_intensity);
        acum_color.set_green(acum_color.get_green() * light_intensity);
        acum_color.set_blue(acum_color.get_blue() * light_intensity);
        diffuse_color = diffuse_color + acum_color;//=> Acumulamos la luz que recibe el punto de interseccion
    }
    return diffuse_color;
}

color new_scene::calculate_specular(ray& rayo, vector3 intersection_point, vector3 intersection_normal, object* nearest_obj)
{
    color specular_color = {0, 0, 0};
    if(nearest_obj->get_shininess() > 0.0f)
    {
        for(light* luz : lights_)
        {
            vector3 rayo_s = (luz->get_position() - intersection_point).normalize();
            
            ray sombra = ray(intersection_point - rayo_s, rayo_s);
            bool hay_sombra = false;
            for(object* obj : objects_)
            {
                vector3 inter = {0, 0, 0};
                vector3 trash1 = {0, 0, 0};
                if(obj->test_intersection(sombra, inter, trash1))
                {
                    double intersection_distance = (inter - intersection_point).get_norm();
                    double light_distance = (luz->get_position() - intersection_point).get_norm();
                    if(intersection_distance > light_distance)//si intersecto con otro objeto pero mas lejos que la ubicacion de la luz, entonces le llega luz
                    {
                        continue;
                    }
                    hay_sombra = true;
                    break;
                }
            }
            if(!hay_sombra)
            {
                vector3 light_ray = sombra.get_ray_vector().normalize();
                vector3 reflection_vector = (light_ray - (intersection_normal * 2 * light_ray.dot_product(intersection_normal))).normalize();
                vector3 camera_vector = rayo.get_ray_vector().normalize();
                double prod = reflection_vector.dot_product(camera_vector);
                if(prod > 0.0f)
                {
                    double specular_intensity = nearest_obj->get_reflectivity() * pow(prod, nearest_obj->get_shininess());
                    specular_color = specular_color + (luz->get_color() * specular_intensity);
                }
            }
        }
    }
    return specular_color;
}
