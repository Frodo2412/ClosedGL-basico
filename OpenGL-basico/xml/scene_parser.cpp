#include "scene_parser.h"

#include <string>

vector3 scene_parser::parse_vector3(const char* str, tinyxml2::XMLElement* element)
{
    const auto vector = element->FirstChildElement(str);
    if (!vector)
    {
        throw std::runtime_error(
            "Attribute " + std::string(str) + " not found on element " + std::string(element->Parent()->Value()));
    }

    const auto x = vector->FloatAttribute("x");
    const auto y = vector->FloatAttribute("y");
    const auto z = vector->FloatAttribute("z");

    return {x, y, z};
}

color scene_parser::parse_color(tinyxml2::XMLElement* element)
{
    const auto fill = element->FirstChildElement("color");

    const auto red = fill->FloatAttribute("red");
    const auto green = fill->FloatAttribute("green");
    const auto blue = fill->FloatAttribute("blue");

    return {red, green, blue};
}

plane* scene_parser::parse_plane(tinyxml2::XMLElement* element)
{
    const auto id = std::string(element->Attribute("id"));
    const auto width = element->FloatAttribute("width");
    const auto height = element->FloatAttribute("height");
    const auto reflectivity = element->FloatAttribute("reflectivity");
    const auto shininess = element->FloatAttribute("shininess");
    const auto translucency = element->FloatAttribute("translucency");
    const auto refractive_index = element->FloatAttribute("refractive_index");

    const auto color = parse_color(element);
    const auto properties = element->FirstChildElement("properties");

    const vector3 position = parse_vector3("position", properties);
    const vector3 normal = parse_vector3("normal", properties);

    std::cout << id << "\n- " << position << "\n- " << normal << "\n- " << color << "\n- " << width << "\n- " << height
        << '\n';

    return new plane(position, normal, color, width, height, reflectivity, shininess, translucency, refractive_index);
}

sphere* scene_parser::parse_sphere(tinyxml2::XMLElement* element)
{
    const auto id = std::string(element->Attribute("id"));
    const auto radius = element->FloatAttribute("radius");
    const auto reflectivity = element->FloatAttribute("reflectivity");
    const auto shininess = element->FloatAttribute("shininess");
    const auto translucency = element->FloatAttribute("translucency");
    const auto refractive_index = element->FloatAttribute("refractive_index");

    const auto color = parse_color(element);
    const auto properties = element->FirstChildElement("properties");
    const auto position = parse_vector3("position", properties);

    std::cout << id << "\n- " << position << "\n- " << radius << "\n- " << color << '\n';

    return new sphere(position, radius, color, reflectivity, shininess, translucency, refractive_index);
}

cylinder* scene_parser::parse_cylinder(tinyxml2::XMLElement* element)
{
    const auto id = std::string(element->Attribute("id"));
    const auto radius = element->FloatAttribute("radius");
    const auto height = element->FloatAttribute("height");
    const auto reflectivity = element->FloatAttribute("reflectivity");
    const auto shininess = element->FloatAttribute("shininess");
    const auto translucency = element->FloatAttribute("translucency");
    const auto refractive_index = element->FloatAttribute("refractive_index");

    const auto color = parse_color(element);
    const auto properties = element->FirstChildElement("properties");

    const auto position = parse_vector3("position", properties);
    const auto axis = parse_vector3("axis", properties);

    std::cout << id << "\n- " << position << "\n- " << radius << "\n- " << height << "\n- " << axis << "\n- " << color
        << '\n';

    return new cylinder(position, radius, height, axis, color, reflectivity, shininess, translucency, refractive_index);
}

mesh* scene_parser::parse_mesh(tinyxml2::XMLElement* element)
{
    const auto id = std::string(element->Attribute("id"));
    const auto width = element->FloatAttribute("width");
    const auto height = element->FloatAttribute("height");
    const auto depth = element->FloatAttribute("depth");
    const auto reflectivity = element->FloatAttribute("reflectivity");
    const auto shininess = element->FloatAttribute("shininess");
    const auto translucency = element->FloatAttribute("translucency");
    const auto refractive_index = element->FloatAttribute("refractive_index");

    const auto color = parse_color(element);
    const auto properties = element->FirstChildElement("properties");

    const auto position = parse_vector3("position", properties);

    std::cout << id << "\n- " << position << "\n- " << width << "\n- " << height << "\n- " << depth << "\n- " << color
        << '\n';

    return new mesh(mesh::create_rectangular_prism(position, width, height, depth, color, reflectivity, shininess,
                                                   translucency, refractive_index));
}

camera* scene_parser::parse_camera(tinyxml2::XMLElement* element, const int width, const int height)
{
    const auto position = parse_vector3("position", element);
    const auto look_at = parse_vector3("look_at", element);
    const auto up = parse_vector3("up", element);

    return new camera(position, look_at, up, width, height);
}

object* scene_parser::parse_object(tinyxml2::XMLElement* element)
{
    const auto object_type = std::string(element->Attribute("type"));

    object* obj;

    if (object_type == "plane") { obj = parse_plane(element); }
    else if (object_type == "sphere") { obj = parse_sphere(element); }
    else if (object_type == "cylinder") { obj = parse_cylinder(element); }
    else if (object_type == "mesh") { obj = parse_mesh(element); }
    else { throw std::runtime_error("Unknown object type"); }

    return obj;
}

light* scene_parser::parse_light(tinyxml2::XMLElement* element)
{
    const auto id = std::string(element->Attribute("id"));
    const auto position = parse_vector3("position", element);
    const auto color = parse_color(element);
    const auto intensity = element->FloatAttribute("intensity");

    std::cout << id << "\n- " << position << "\n- " << color << "\n- " << intensity << '\n';

    return new light(position, color, intensity);
}

int scene_parser::parse_int(const tinyxml2::XMLElement* xml_element, const char* str)
{
    return xml_element->IntAttribute(str);
}
