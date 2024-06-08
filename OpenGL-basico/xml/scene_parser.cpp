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
    const auto fill = element->FirstChildElement("fill");

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

    const auto color = parse_color(element);
    const auto properties = element->FirstChildElement("properties");

    const vector3 position = parse_vector3("position", properties);
    const vector3 normal = parse_vector3("normal", properties);

    std::cout << id << position << " " << normal << " " << color << " " << width << " " << height << std::endl;

    return new plane(position, normal, color, width, height);
}

sphere* scene_parser::parse_sphere(tinyxml2::XMLElement* element)
{
    const auto id = std::string(element->Attribute("id"));
    const auto radius = element->FloatAttribute("radius");

    const auto color = parse_color(element);
    const auto properties = element->FirstChildElement("properties");
    const auto position = parse_vector3("position", properties);

    std::cout << id << position << " " << radius << " " << color << '\n';

    return new sphere(position, radius, color);
}

cylinder* scene_parser::parse_cylinder(tinyxml2::XMLElement* element)
{
    const auto id = std::string(element->Attribute("id"));
    const auto radius = element->FloatAttribute("radius");
    const auto height = element->FloatAttribute("height");

    const auto color = parse_color(element);
    const auto properties = element->FirstChildElement("properties");

    const auto position = parse_vector3("position", properties);
    const auto axis = parse_vector3("axis", properties);

    std::cout << id << position << " " << radius << " " << height << " " << axis << " " << color << '\n';

    return new cylinder(position, radius, height, axis, color);
}

void scene_parser::parse_object(tinyxml2::XMLElement* element)
{
    const auto object_type = std::string(element->Attribute("type"));

    object* obj;

    if (object_type == "plane") { obj = parse_plane(element); }
    else if (object_type == "sphere") { obj = parse_sphere(element); }
    else if (object_type == "cylinder") { obj = parse_cylinder(element); }
    else { throw std::runtime_error("Unknown object type"); }

    objects_.push_back(obj);
}

void scene_parser::parse_light(tinyxml2::XMLElement* element)
{
}

new_scene scene_parser::from_xml(const char* filename)
{
    tinyxml2::XMLDocument doc;
    auto res = doc.LoadFile(filename);
    if (res != tinyxml2::XML_SUCCESS)
    {
        throw std::runtime_error("Failed to load file " + std::string(filename) + ": " + std::to_string(res));
    }

    tinyxml2::XMLPrinter printer;
    doc.Print(&printer);

    auto dom_scene = doc.FirstChildElement("document")->FirstChildElement("scene");
    if (!dom_scene)
    {
        throw std::runtime_error("'scene' element not found");
    }

    if (dom_scene->NoChildren())
    {
        throw std::runtime_error("No objects found in scene");
    }

    tinyxml2::XMLNode* node = dom_scene->FirstChild();
    do
    {
        const auto element = node->ToElement();

        const auto element_type = std::string(element->Name());

        if (element_type == "shape") { parse_object(element); }
        else if (element_type == "light") { parse_light(element); }
        else { throw std::runtime_error("Unknown element type: " + element_type); }

        node = node->NextSibling();
    }
    while (node != nullptr);

    vector3 cylinder1_pos = {0, -6, -8};
    color cylinder1_color = {0, 255, 0};
    cylinder* cylinder0 = new cylinder(cylinder1_pos, 2, 5, {0, 1, 0}, cylinder1_color);
    objects_.push_back(cylinder0);

    //luces
    light* light0 = new light({5, 5, 0}, {255, 255, 255}, 0.5f);
    lights_.push_back(light0);

    light* light1 = new light({-10, 0, 0}, {255, 255, 255}, 0.5f);
    lights_.push_back(light1);

    std::cout << "Scene loaded" << '\n' << "- Shapes: " << objects_.size() << '\n' << "- Lights: " << lights_.size() <<
        '\n';

    return new_scene{width_, height_, objects_, lights_};
}
