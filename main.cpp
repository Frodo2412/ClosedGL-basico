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
        vector3(10, 10, 0),
        vector3(20, 10, 0),
        vector3(20, 20, 0),
        vector3(10, 20, 0)
    );

    auto scene = ::scene(square);

    renderer::render_image(width, height, scene);

    FreeImage_DeInitialise();

    return 0;
}
