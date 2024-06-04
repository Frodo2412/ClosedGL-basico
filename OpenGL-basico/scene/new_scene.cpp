﻿#include "new_scene.h"
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
    plane* plane0 = new plane(plane0_pos, plane0_normal, plane0_color);
    objects_.push_back(plane0);
    // plano del techo
    vector3 plane1_pos = {0, 50, -50};
    vector3 plane1_normal = {0, -1, 0};
    color plane1_color = {100, 100, 100};
    plane* plane1 = new plane(plane1_pos, plane1_normal, plane1_color);
    objects_.push_back(plane1);
    // plano del piso
    vector3 plane2_pos = {0, -50, -50};
    vector3 plane2_normal = {0, 1, 0};
    color plane2_color = {255, 255, 255};
    plane* plane2 = new plane(plane2_pos, plane2_normal, plane2_color);
    objects_.push_back(plane2);
    // plano de la izquierda
    vector3 plane3_pos = {-50, 0, 0};
    vector3 plane3_normal = {1, 0, 0};
    color plane3_color = {255, 0, 0};
    plane* plane3 = new plane(plane3_pos, plane3_normal, plane3_color);
    objects_.push_back(plane3);
    // plano de la derecha
    vector3 plane4_pos = {50, 0, 0};
    vector3 plane4_normal = {-1, 0, 0};
    color plane4_color = {0, 255, 0};
    plane* plane4 = new plane(plane4_pos, plane4_normal, plane4_color);
    objects_.push_back(plane4);

    //dibujado de esferas
    vector3 sphere0_pos = {0, 0, -30};
    color sphere0_color = {255, 0, 0};
    sphere* sphere0 = new sphere(sphere0_pos, 20, sphere0_color);
    objects_.push_back(sphere0);
    
    light* light0 = new light({0, 5, 0}, {255, 255, 255}, 1);
    lights_.push_back(light0);
}

image new_scene::Render()
{
    std::vector<std::vector<float>> z_buffer(width_, std::vector<float>(height_));
    float near = 0.1;
    float far = 100;
    color background_color = {0, 0, 0};
    std::vector<pixel> pixels;
    for(int x = 0 ; x < width_ ; x++)
    {
        for(int y = 0 ; y < height_ ; y++)
        {
            pixel px = pixel(x,y, background_color);
            z_buffer[x][y] = far;
            pixels.push_back(px);
        }
    }
    
    ray rayo = ray(camera_->get_position(), {0, 0, 0});
    
    vector3 intersection_point;
    vector3 normal;
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
                bool intersection = obj->test_intersection(rayo, intersection_point, normal, load_color);
                if (intersection)
                {
                    px_color = obj->get_color();
                    vector3 L = intersection_point - camera_->get_position();
                    float distance = L.get_norm();
                
                    if(distance < far && distance > near)
                    {
                        if(distance < z_buffer[x][y])
                        {
                            z_buffer[x][y] = distance;
                            px_color.set_red(px_color.get_red() - px_color.get_red() * (distance/far));
                            px_color.set_green(px_color.get_green() - px_color.get_green() * (distance/far));
                            px_color.set_blue(px_color.get_blue() - px_color.get_blue() * (distance/far));

                            pixel px = pixel(x,y, px_color);
                            pixels.push_back(px);
                        }
                    } 
                }
            }
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
