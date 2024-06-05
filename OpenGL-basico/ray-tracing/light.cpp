#include "light.h"

#include <iostream>

bool light::compute_illumination(vector3 &intersection_point, vector3 &normal, std::vector<object*> objects, object* current, color & color, float & intensity)
{
    vector3 rayo_s = (get_position() - intersection_point).normalize();
    vector3 start = intersection_point;
    float prod = normal.dot_product(rayo_s);
    if(prod > 0.0f)
    {
        color = get_color();
        intensity = get_intensity() * prod;
    } else
    {
        color = get_color();
        intensity = 0.0f;
    }
    return true;
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