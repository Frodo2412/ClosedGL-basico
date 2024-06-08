#include "new_scene.h"
#include <vector>
#include "../ray-tracing/plane.h"
#include "../ray-tracing/sphere.h"
#include "../ray-tracing/cylinder.h"

new_scene::new_scene(int width, int height)
{
    background_color_ = {0, 0, 0};
    near_ = 0.1f;
    far_ = 100;
    width_ = width;
    height_ = height;
    vector3 cam_position = {0, 0, 0};
    vector3 cam_look_at = {0, 0, -1}; //nuestro sistema de coordenadas tiene el z invertido, quedo como en lo teniamos en opengl
    vector3 cam_up = {0, 1, 0};
    camera_ = new camera(cam_position, cam_look_at, cam_up);

    //dibujado de planos
    // plano del fondo
    vector3 plane0_pos = {0, 0, -50};
    vector3 plane0_normal = {0, 0, 1};
    color plane0_color = {255, 255, 255};
    plane* plane0 = new plane(plane0_pos, plane0_normal, plane0_color, 50, 50, 0.0f, 0.0f);
    objects_.push_back(plane0);
    // plano del techo
    vector3 plane1_pos = {0, 50, -50};
    vector3 plane1_normal = {0, -1, 0};
    color plane1_color = {100, 100, 100};
    plane* plane1 = new plane(plane1_pos, plane1_normal, plane1_color, 50, 50, 1.f, 10.0f);
    objects_.push_back(plane1);
    // plano del piso
    vector3 plane2_pos = {0, -50, -50};
    vector3 plane2_normal = {0, 1, 0};
    color plane2_color = {255, 255, 255};
    plane* plane2 = new plane(plane2_pos, plane2_normal, plane2_color, 50, 50, 0.0f, 0.0f);
    objects_.push_back(plane2);
    // plano de la izquierda
    vector3 plane3_pos = {-50, 0, 0};
    vector3 plane3_normal = {1, 0, 0};
    color plane3_color = {255, 0, 0};
    plane* plane3 = new plane(plane3_pos, plane3_normal, plane3_color, 50, 50, 0.0f, 0.0f);
    objects_.push_back(plane3);
    // plano de la derecha
    vector3 plane4_pos = {50, 0, 0};
    vector3 plane4_normal = {-1, 0, 0};
    color plane4_color = {0, 255, 0};
    plane* plane4 = new plane(plane4_pos, plane4_normal, plane4_color, 50, 50, 0.0f, 0.0f);
    objects_.push_back(plane4);

    // mesa front
    vector3 mesa_front_pos = {0, -10, -10};
    vector3 mesa_front_normal = {0, 0, 1};
    color mesa_front_color = {255, 0, 255};
    plane* mesa_front = new plane(mesa_front_pos, mesa_front_normal, mesa_front_color, 5, 2, 0.0f, 0.0f);
    objects_.push_back(mesa_front);

    // mesa up
    vector3 mesa_mesa_up_pos = {0, -8, -12};
    vector3 mesa_mesa_up_normal = {0, 1, 0};
    color mesa_mesa_up_color = {0, 255, 255};
    plane* mesa_mesa_up = new plane(mesa_mesa_up_pos, mesa_mesa_up_normal, mesa_mesa_up_color, 2, 5, 0.0f, 0.0f);
    objects_.push_back(mesa_mesa_up);

    //dibujado de esferas
    vector3 sphere0_pos = {5, 0, -20};
    color sphere0_color = {255, 0, 0};
    sphere* sphere0 = new sphere(sphere0_pos, 10, sphere0_color, 0.5f, 10.f);
    objects_.push_back(sphere0);

    vector3 sphere1_pos = {-1, -1, -2};
    color sphere1_color = {255, 255, 0};
    sphere* sphere1 = new sphere(sphere1_pos, 1, sphere1_color, 0.5f, 10.0f);
    objects_.push_back(sphere1);

    vector3 sphere2_pos = {1, 0, -5};
    color sphere2_color = {0, 255, 255};
    sphere* sphere2 = new sphere(sphere2_pos, 1, sphere2_color, 0.0f, 0.0f);
    //objects_.push_back(sphere2);

    vector3 cylinder1_pos = {0, -6, -8};
    color cylinder1_color = {0, 255, 0};
    cylinder* cylinder0 = new cylinder(cylinder1_pos, 2, 5, {0,1, 0}, cylinder1_color, 0.0f, 0.0f);
    //objects_.push_back(cylinder0);

    //luces
    light* light0 = new light({0, -5, 0}, {255, 255, 255}, 0.5f);
    lights_.push_back(light0);

    light* light1 = new light({-10, 0, 0}, {255, 255, 255}, 0.5f);
    lights_.push_back(light1);
}

image new_scene::Render()
{
    /* Vector donde se ira guardando el color (luz) acumulado por cada pixel */
    std::vector<pixel> pixels;

    /* Creamos el rayo que sale de la camara, el cual usaremos para el trazado de rayos */
    ray rayo = ray(camera_->get_position(), {0, 0, 0});

    /* Variables para normalizar a [-1, 1] las dimensiones de la camara */
    float x_factor = 2.0f / (float)width_;
    float y_factor = 2.0f / (float)height_;
    
    /* Caculamos todos los pixeles */
    for(int x = 0 ; x < width_ ; x++)
    {
        for(int y = 0 ; y < height_ ; y++)
        {
            /* Normalizamos el pixel por el que pasara el rayo */
            float norm_x = (float)x * x_factor - 1.0f;
            float norm_y = (float)y * y_factor - 1.0f;

            /* Casteamos el rayo para que pase por el pixel normalizado (x, y) */
            camera_->generate_ray(norm_x, norm_y, rayo);
            
            pixel px = pixel(x, y, whitted_ray_tracing(rayo));
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

float new_scene::get_far()
{
    return far_;
}

float new_scene::get_near()
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
    float z_buffer = get_far();
    
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
            float distance = (i_point - camera_->get_position()).get_norm();//=> Distancia entre la camara y el punto de interseccion
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
    float light_intensity = 0;//=> Variable en la que cargaremos la intensidad de la luz en el punto de interseccion
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
            
            ray sombra = ray(intersection_point, rayo_s);
            bool hay_sombra = false;
            for(object* obj : objects_)
            {
                if (obj != nearest_obj)
                {
                    vector3 inter = {0, 0, 0};
                    vector3 trash1 = {0, 0, 0};
                    if(obj->test_intersection(sombra, inter, trash1))
                    {
                        float intersection_distance = (inter - intersection_point).get_norm();
                        float light_distance = (luz->get_position() - intersection_point).get_norm();
                        if(intersection_distance > light_distance)//si intersecto con otro objeto pero mas lejos que la ubicacion de la luz, entonces le llega luz
                        {
                            continue;
                        }
                        hay_sombra = true;
                        break;
                    }
                }
            }
            if(!hay_sombra)
            {
                vector3 light_ray = sombra.get_ray_vector().normalize();
                vector3 reflection_vector = (light_ray - (intersection_normal * 2 * light_ray.dot_product(intersection_normal))).normalize();
                vector3 camera_vector = rayo.get_ray_vector().normalize();
                float prod = reflection_vector.dot_product(camera_vector);
                if(prod > 0.0f)
                {
                    float specular_intensity = nearest_obj->get_reflectivity() * pow(prod, nearest_obj->get_shininess());
                    specular_color = specular_color + (luz->get_color() * specular_intensity);
                }
            }
        }
    }
    return specular_color;
}
