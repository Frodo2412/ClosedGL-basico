#include "new_scene.h"
#include <vector>
#include "../ray-tracing/plane.h"
#include "../ray-tracing/sphere.h"

new_scene::new_scene(int width, int height)
{
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
    plane* plane0 = new plane(plane0_pos, plane0_normal, plane0_color, 50, 50);
    objects_.push_back(plane0);
    // plano del techo
    vector3 plane1_pos = {0, 50, -50};
    vector3 plane1_normal = {0, -1, 0};
    color plane1_color = {100, 100, 100};
    plane* plane1 = new plane(plane1_pos, plane1_normal, plane1_color, 50, 50);
    objects_.push_back(plane1);
    // plano del piso
    vector3 plane2_pos = {0, -50, -50};
    vector3 plane2_normal = {0, 1, 0};
    color plane2_color = {255, 255, 255};
    plane* plane2 = new plane(plane2_pos, plane2_normal, plane2_color, 50, 50);
    objects_.push_back(plane2);
    // plano de la izquierda
    vector3 plane3_pos = {-50, 0, 0};
    vector3 plane3_normal = {1, 0, 0};
    color plane3_color = {255, 0, 0};
    plane* plane3 = new plane(plane3_pos, plane3_normal, plane3_color, 50, 50);
    objects_.push_back(plane3);
    // plano de la derecha
    vector3 plane4_pos = {50, 0, 0};
    vector3 plane4_normal = {-1, 0, 0};
    color plane4_color = {0, 255, 0};
    plane* plane4 = new plane(plane4_pos, plane4_normal, plane4_color, 50, 50);
    objects_.push_back(plane4);

    // mesa front
    vector3 mesa_front_pos = {0, -10, -10};
    vector3 mesa_front_normal = {0, 0, 1};
    color mesa_front_color = {255, 0, 255};
    plane* mesa_front = new plane(mesa_front_pos, mesa_front_normal, mesa_front_color, 5, 2);
    objects_.push_back(mesa_front);

    // mesa up
    vector3 mesa_mesa_up_pos = {0, -8, -12};
    vector3 mesa_mesa_up_normal = {0, 1, 0};
    color mesa_mesa_up_color = {0, 255, 255};
    plane* mesa_mesa_up = new plane(mesa_mesa_up_pos, mesa_mesa_up_normal, mesa_mesa_up_color, 2, 5);
    objects_.push_back(mesa_mesa_up);

    //dibujado de esferas
    vector3 sphere0_pos = {0, 0, -20};
    color sphere0_color = {255, 0, 0};
    sphere* sphere0 = new sphere(sphere0_pos, 10, sphere0_color);
    objects_.push_back(sphere0);

    vector3 sphere1_pos = {-1, -1, -5};
    color sphere1_color = {255, 255, 0};
    sphere* sphere1 = new sphere(sphere1_pos, 1, sphere1_color);
    objects_.push_back(sphere1);

    vector3 sphere2_pos = {1, 0, -5};
    color sphere2_color = {0, 255, 255};
    sphere* sphere2 = new sphere(sphere2_pos, 1, sphere2_color);
    objects_.push_back(sphere2);

    //luces
    light* light0 = new light({5, 5, 0}, {255, 255, 255}, 0.5f);
    lights_.push_back(light0);

    light* light1 = new light({-10, 0, 0}, {255, 255, 255}, 0.5f);
    lights_.push_back(light1);
}

image new_scene::Render()
{
    /* Matriz donde se guardara la distancia al objeto mas cercano en cada pixel */
    std::vector<std::vector<float>> z_buffer(width_, std::vector<float>(height_));
    
    /* Matriz donde se ira guardando el color (luz) acumulado por cada pixel */
    std::vector<std::vector<color>> pixel_colors(width_, std::vector<color>(height_));
    
    float near = 0.1f;//=> Distancia minima a la que se puede renderizar un objeto
    float far = 100;//=> Distancia maxima a la que se puede renderizar un objeto

    /* Color de fondo de la escena */
    color background_color = {0, 0, 0};

    /* Inicializamos el color para todos los pixeles como el background color y
       la distancia minima de cada pixel como la maxima a renderizar posible */
    for(int x = 0 ; x < width_ ; x++)
    {
        for(int y = 0 ; y < height_ ; y++)
        {
            pixel_colors[x][y] = background_color;
            z_buffer[x][y] = far;
        }
    }

    /* Creamos el rayo que sale de la camara, el cual usaremos para el trazado de rayos */
    ray rayo = ray(camera_->get_position(), {0, 0, 0});
    
    vector3 intersection_point = {0, 0, 0};//=> Variable en la que cargaremos el punto de interseccion con los objetos
    vector3 intersection_normal = {0, 0, 0};//=> Variable en la que cargaremos la normal del objeto en el punto de interseccion
    color px_color = {0, 0, 0};//=> Variable en la que cargaremos el color del pixel
    float light_intensity = 0;//=> Variable en la que cargaremos la intensidad de la luz en el punto de interseccion

    /* Variables para normalizar a [-1, 1] las dimensiones de la camara */
    float x_factor = 2.0f / (float)width_;
    float y_factor = 2.0f / (float)height_;
    
    /* Whitted Ray-Tracing */
    for(int x = 0 ; x < width_ ; x++)
    {
        for(int y = 0 ; y < height_ ; y++)
        {
            /* Normalizamos el pixel por el que pasara el rayo */
            float norm_x = (float)x * x_factor - 1.0f;
            float norm_y = (float)y * y_factor - 1.0f;

            /* Casteamos el rayo para que pase por el pixel normalizado (x, y) */
            camera_->generate_ray(norm_x, norm_y, rayo);

            /* Para cada objeto en la escena calcularemos si el rayo interseca con este  */
            for(object* obj : objects_)
            {
                /* Si el rayo interseca con el objeto entonces procederemos a calcular si esta iluminado en ese punto,
                   en otro caso hay 2 opciones:
                        - el rayo se intersecte con otro objeto => el color de pixel lo va a dar otro objeto
                        - el rayo no se intersecte nunca con un objeto => color de pixel = background color(ya esta cargado por default este caso)
                */
                if (obj->test_intersection(rayo, intersection_point, intersection_normal))
                {
                    float distance = (intersection_point - camera_->get_position()).get_norm();//=> Distancia entre la camara y el punto de interseccion
                    if(distance < far && distance > near)// => checkeamos si el punto de interseccion esta en el rango de renderizado
                    {
                        /* Si el punto de interseccion esta mas cerca que el mas cercano obtenido hasta hora para ese pixel
                           significa que se va a ver ese nuevo punto en vez del viejo, porque simplemente esta delante y tapa al otro */
                        if(distance < z_buffer[x][y])
                        {
                            /* Reseatemos el color para ese pixel asi partimos de 0 para agregarle la cantidad de luz que recibe
                               el punto de interseccion */
                            pixel_colors[x][y] = background_color;
                            z_buffer[x][y] = distance;
                            
                            /* Calcularemos cuanta luz recibe el punto de interseccion */
                            for(light* luz : lights_)
                            {
                                /* Veremos si teniendo en cuenta la luz puntual "Luz" el punto de interseccion esta en sombra o no*/
                                luz->compute_illumination(intersection_point, intersection_normal, objects_, obj, light_intensity);
                                px_color = obj->get_color();
                                px_color.set_red(px_color.get_red() * light_intensity);
                                px_color.set_green(px_color.get_green() * light_intensity);
                                px_color.set_blue(px_color.get_blue() * light_intensity);
                                pixel_colors[x][y] = pixel_colors[x][y] + px_color;//=> Acumulamos la luz que recibe el punto de interseccion
                            }
                        }
                    } 
                }
            }
        }
    }
    std::vector<pixel> pixels;
    for (int x = 0; x < width_; x++)
    {
        for (int y = 0; y < height_; y++)
        {
            pixel px = pixel(x, y, pixel_colors[x][y]);
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

