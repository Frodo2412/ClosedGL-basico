#include <iostream>

#include "Freeimage/FreeImage.h"
#include "OpenGL-basico/graphics/renderer.h"
#include "OpenGL-basico/scene/new_scene.h"
#include "OpenGL-basico/xml/scene_parser.h"

int main(int argc, char* argv[])
{
    try
    {
        FreeImage_Initialise();

        auto scene = new_scene("../scenes/scene.xml");
        for (image img : scene.Render())
        {
            renderer::render_image(img); // renders image to screen
        }

        FreeImage_DeInitialise();
        return 0;
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
}
