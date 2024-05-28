#include "Freeimage/FreeImage.h"
#include "OpenGL-basico/geometry/square.h"
#include "OpenGL-basico/graphics/renderer.h"
#include "OpenGL-basico/scene/scene.h"

int main(int argc, char* argv[])
{
    // Initialize FreeImage library
    FreeImage_Initialise();

    // Define image dimensions
    const int width = 800;
    const int height = 600;

    auto square = ::square(
        vector3(10, 10, 1),
        vector3(30, 10, 10),
        vector3(30, 30, 1),
        vector3(10, 30, 1)
    );

    scene * scene_ = new scene(square);

    renderer::render_image(width, height, scene_);

    FreeImage_DeInitialise();

    return 0;
}
