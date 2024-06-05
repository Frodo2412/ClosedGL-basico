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
    //objects_.push_back(plane1);
    // plano del piso
    vector3 plane2_pos = {0, -50, -50};
    vector3 plane2_normal = {0, 1, 0};
    color plane2_color = {255, 255, 255};
    plane* plane2 = new plane(plane2_pos, plane2_normal, plane2_color, 50, 50);
    //objects_.push_back(plane2);
    // plano de la izquierda
    vector3 plane3_pos = {-50, 0, 0};
    vector3 plane3_normal = {1, 0, 0};
    color plane3_color = {255, 0, 0};
    plane* plane3 = new plane(plane3_pos, plane3_normal, plane3_color, 50, 50);
    //objects_.push_back(plane3);
    // plano de la derecha
    vector3 plane4_pos = {50, 0, 0};
    vector3 plane4_normal = {-1, 0, 0};
    color plane4_color = {0, 255, 0};
    plane* plane4 = new plane(plane4_pos, plane4_normal, plane4_color, 50, 50);
    //objects_.push_back(plane4);

    // mesa front
    vector3 mesa_front_pos = {0, -10, -10};
    vector3 mesa_front_normal = {0, 0, 1};
    color mesa_front_color = {255, 0, 255};
    plane* mesa_front = new plane(mesa_front_pos, mesa_front_normal, mesa_front_color, 5, 2);
    //objects_.push_back(mesa_front);

    // mesa up
    vector3 mesa_mesa_up_pos = {0, -8, -12};
    vector3 mesa_mesa_up_normal = {0, 1, 0};
    color mesa_mesa_up_color = {0, 255, 255};
    plane* mesa_mesa_up = new plane(mesa_mesa_up_pos, mesa_mesa_up_normal, mesa_mesa_up_color, 2, 5);
    //objects_.push_back(mesa_mesa_up);

    //dibujado de esferas
    vector3 sphere0_pos = {0, 0, -20};
    color sphere0_color = {255, 0, 0};
    sphere* sphere0 = new sphere(sphere0_pos, 10, sphere0_color);
    objects_.push_back(sphere0);

    vector3 sphere1_pos = {-1, 0, -5};
    color sphere1_color = {255, 255, 0};
    sphere* sphere1 = new sphere(sphere1_pos, 1, sphere1_color);
    objects_.push_back(sphere1);

    //luces
    light* light0 = new light({5, -5, 0}, {255, 255, 255}, 1.0f);
    lights_.push_back(light0);

    light* light1 = new light({-5, 5, 0}, {255, 255, 255}, 0.3f);
    //lights_.push_back(light1);
}

image new_scene::Render()
{
    std::vector<std::vector<float>> z_buffer(width_, std::vector<float>(height_));
    std::vector<std::vector<color>> pixel_colors(width_, std::vector<color>(height_));
    float near = 0.1;
    float far = 100;
    color background_color = {0, 0, 0};
    
    for(int x = 0 ; x < width_ ; x++)
    {
        for(int y = 0 ; y < height_ ; y++)
        {
            pixel_colors[x][y] = background_color;
            z_buffer[x][y] = far;
        }
    }
    
    ray rayo = ray(camera_->get_position(), {0, 0, 0});
    
    vector3 intersection_point = {0, 0, 0};
    vector3 intersection_normal = {0, 0, 0};
    color load_color = {0, 0, 0};
    color px_color = {0, 0, 0};
    float x_factor = 2.0f / (float)width_;
    float y_factor = 2.0f / (float)height_;
    for(int x = 0 ; x < width_ ; x++)
    {
        for(int y = 0 ; y < height_ ; y++)
        {
            float norm_x = (float)x * x_factor - 1.0f;
            float norm_y = (float)y * y_factor - 1.0f;
            camera_->generate_ray(norm_x, norm_y, rayo);
            for(object* obj : objects_)
            {
                bool intersection = obj->test_intersection(rayo, intersection_point, intersection_normal, load_color);
                if (intersection)
                {
                    vector3 L = intersection_point - camera_->get_position();
                    float distance = L.get_norm();
                    if(distance < far && distance > near)
                    {
                        if(distance < z_buffer[x][y])
                        {
                            pixel_colors[x][y] = background_color;
                            z_buffer[x][y] = distance;
                            bool hay_luz = false;
                            float intensity = 0;
                            for(light* luz : lights_)
                            {
                                hay_luz = luz->compute_illumination(intersection_point, intersection_normal, objects_, obj, load_color, intensity);
                                if (hay_luz)
                                {
                                    px_color = obj->get_color();
                                    px_color.set_red(px_color.get_red() * intensity);
                                    px_color.set_green(px_color.get_green() * intensity);
                                    px_color.set_blue(px_color.get_blue() * intensity);
                                    pixel_colors[x][y] = pixel_colors[x][y] + px_color;
                                } else
                                {
                                    pixel_colors[x][y] = {0,0,0};
                                }
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

