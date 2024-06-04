#include "new_scene.h"
#include <vector>

new_scene::new_scene(int width, int height)
{
    width_ = width;
    height_ = height;
    vector3 cam_position = {0, 0, 0};
    vector3 cam_look_at = {0, 0, -1}; //nuestro sistema de coordenadas tiene el z invertido, quedo como en lo teniamos en opengl
    vector3 cam_up = {0, 1, 0};
    camera_ = new camera(cam_position, cam_look_at, cam_up);
    vector3 sphere_pos = {5, 0, -10};
    color sphere_color = {255, 0, 0};
    sphere_ = new sphere(sphere_pos, 5, sphere_color);
}

image new_scene::Render()
{
    ray rayo = ray(camera_->get_position(), {0, 0, 0});
    vector3 point;
    vector3 normal;
    color background_color = {0, 100, 100};
    std::vector<pixel> pixels;
    float x_factor = 2.0f / (float)width_;
    float y_factor = 2.0f / (float)height_;
    for(int x = 0 ; x < width_ ; x++)
    {
        for(int y = 0 ; y < height_ ; y++)
        {
            float norm_x = (float)x * x_factor - 1.0f;
            float norm_y = (float)y * y_factor - 1.0f;
            camera_->generate_ray(norm_x, norm_y, rayo);
            bool intersection = sphere_->test_intersection(rayo, point, normal, sphere_->get_color());
            if (intersection)
            {
                pixel px = pixel(x,y, sphere_->get_color());
                pixels.push_back(px);
            } else
            {
                pixel px = pixel(x,y, background_color);
                pixels.push_back(px);
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
