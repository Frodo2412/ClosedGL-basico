#include "new_scene.h"
#include <utility>
#include <vector>
#include "../ray-tracing/plane.h"

new_scene::new_scene(int width, int height, std::vector<object*> objects, std::vector<light*> lights)
{
    background_color_ = {0, 0, 0};
    near_ = 0.1;
    far_ = 100;
    width_ = width;
    height_ = height;
    vector3 cam_position = {0, 0, 0};
    vector3 cam_look_at = {0, 0, -1};
    //nuestro sistema de coordenadas tiene el z invertido, quedo como en lo teniamos en opengl
    vector3 cam_up = {0, 1, 0};

    camera_ = new camera(cam_position, cam_look_at, cam_up);
    objects_ = std::move(objects);
    lights_ = std::move(lights);
}

image new_scene::Render()
{
    /* Vector donde se ira guardando el color (luz) acumulado por cada pixel */
    std::vector<pixel> pixels;

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

                    // Calculamos el color del rayo
                    color sample_color = whitted_ray_tracing(rayo);

                    // Sumamos el color de la muestra al color final del píxel
                    final_color += sample_color;
                }
            }

            // Promediamos el color final dividiendo por el número de muestras
            final_color = final_color / (n * n);

            // Guardamos el píxel con el color final calculado
            pixel px = pixel(x, y, final_color);
            pixels.push_back(px);
        }
    }
    return image(width_, height_, pixels);
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

color new_scene::whitted_ray_tracing(ray& rayo)
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
    /* Calcularemos cuanta luz recibe el punto de interseccion */
    if(nearest_obj != nullptr)
    {
        color diffuse_color = calculate_diffuse(intersection_point, intersection_normal, nearest_obj);
        color specular_color = calculate_specular(rayo, intersection_point, intersection_normal, nearest_obj);
        px_color = diffuse_color + specular_color;
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
