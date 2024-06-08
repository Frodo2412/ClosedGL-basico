#include <iostream>

#include "Freeimage/FreeImage.h"
#include "OpenGL-basico/graphics/renderer.h"
#include "OpenGL-basico/scene/new_scene.h"

int main(int argc, char* argv[])
{
    FreeImage_Initialise();
    int width = 400;
    int height = 300;

    new_scene* scene = new new_scene(width, height);
    image img = scene->Render();
    renderer::render_image(img); // renders image to screen

    FreeImage_DeInitialise();
    return 0;
}
