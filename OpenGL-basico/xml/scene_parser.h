#pragma once

#include "tinyxml2.h"
#include "../scene/new_scene.h"
#include "../ray-tracing/plane.h"
#include "../ray-tracing/sphere.h"
#include "../ray-tracing/cylinder.h"
#include "../ray-tracing/mesh.h"

class scene_parser
{
    static vector3 parse_vector3(const char* str, tinyxml2::XMLElement* element);

    static plane* parse_plane(tinyxml2::XMLElement* element);
    static sphere* parse_sphere(tinyxml2::XMLElement* element);
    static cylinder* parse_cylinder(tinyxml2::XMLElement* element);
    static mesh* parse_mesh(tinyxml2::XMLElement* element);

public:
    static color parse_color(tinyxml2::XMLElement* element);
    static camera* parse_camera(tinyxml2::XMLElement* element, int width, int height);
    static object* parse_object(tinyxml2::XMLElement* element);
    static light* parse_light(tinyxml2::XMLElement* element);
};
