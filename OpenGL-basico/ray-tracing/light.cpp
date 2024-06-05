#include "light.h"

#include <iostream>

bool light::compute_illumination(vector3 &intersection_point, vector3 &normal, std::vector<object*> objects, object* current, color & color, float & intensity)
{
    vector3 rayo_s = (position_ - intersection_point).normalize();
    float prod = normal.dot_product(rayo_s);
    if(prod > 0.0f)
    {
        ray sombra = ray(intersection_point, rayo_s);
        bool intersection_existed = false;
        for(object* obj : objects)
        {
            if (obj != current)
            {
                vector3 trash = {0, 0, 0};
                vector3 trash1 = {0, 0, 0};
                ::color trash_color = {0, 0, 0};
                intersection_existed = obj->test_intersection(sombra, trash, trash1, trash_color);
                if(intersection_existed)
                {
                    break;
                }
            }
        }
        if (intersection_existed)
        {
            color = get_color();
            intensity = 0.0f;
            return false;
        } else
        {
            color = get_color();
            intensity = get_intensity() * prod;
            return true;
        }
    } else
    {
        color = get_color();
        intensity = 0.0f;
        return false;
    }
}

vector3 light::get_position()
{
    return position_;
}

color light::get_color()
{
    return color_;
}

float light::get_intensity()
{
    return intensity_;
}

light::~light()
{
}