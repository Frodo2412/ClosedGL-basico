#include "light.h"

#include <iostream>

bool light::compute_illumination(vector3 &intersection_point, vector3 &normal, std::vector<object*> objects, object* current, float & intensity)
{
    vector3 rayo_s = (position_ - intersection_point).normalize();
    float prod = normal.dot_product(rayo_s);
    if(prod > 0.0f)
    {
        intensity = get_intensity() * prod;
        /* rayo que va desde el punto de interseccion hacia la luz, si interseca con un objeto significa
          que la fuente de luz esta siendo tapada y por lo tanto tenemos sombra */
        ray sombra = ray(intersection_point, rayo_s);
        
        for(object* obj : objects)
        {
            if (obj != current)
            {
                vector3 inter = {0, 0, 0};
                vector3 trash1 = {0, 0, 0};
                if(obj->test_intersection(sombra, inter, trash1))
                {
                    float intersection_distance = (inter - intersection_point).get_norm();
                    float light_distance = (position_ - intersection_point).get_norm();
                    if(intersection_distance > light_distance)//si intersecto con otro objeto pero mas lejos que la ubicacion de la luz, entonces le llega luz
                    {
                        continue;
                    }
                    intensity = 0.0f;
                    break;
                }
            }
        }
    } else
    {
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