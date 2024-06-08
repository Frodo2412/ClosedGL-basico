#pragma once

#include "tinyxml2.h"
#include "../scene/new_scene.h"
#include "../ray-tracing/plane.h"
#include "../ray-tracing/sphere.h"
#include "../ray-tracing/cylinder.h"

class scene_parser
{
    int width_, height_;
    std::vector<object*> objects_;
    std::vector<light*> lights_;

    static vector3 parse_vector3(const char* str, tinyxml2::XMLElement* element);
    static color parse_color(tinyxml2::XMLElement* element);

    static plane* parse_plane(tinyxml2::XMLElement* element);
    static sphere* parse_sphere(tinyxml2::XMLElement* element);
    static cylinder* parse_cylinder(tinyxml2::XMLElement* element);

    void parse_object(tinyxml2::XMLElement* element);
    void parse_light(tinyxml2::XMLElement* element);

public:
    scene_parser(const int width, const int height): width_(width), height_(height)
    {
    }

    new_scene from_xml(const char* filename);
};
