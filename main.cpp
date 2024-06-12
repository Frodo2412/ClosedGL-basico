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
        int width = 800;
        int height = 600;

        new_scene scene = new_scene(width, height, "../scenes/scene_2.xml");
        for(image img : scene.Render())
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
