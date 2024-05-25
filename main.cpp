
#include "Freeimage/FreeImage.h"
#include "OpenGL-basico/renderer.h"

int main(int argc, char* argv[])
{
    // Initialize FreeImage library
    FreeImage_Initialise();

    // Define image dimensions
    const int width = 800;
    const int height = 600;

    renderer::render_image(width, height);
    
    FreeImage_DeInitialise();
    
    return 0;
}
