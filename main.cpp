#include <iostream>

#include "Freeimage/FreeImage.h"
#include "OpenGL-basico/graphics/renderer.h"
#include "OpenGL-basico/pipelines/projection_pipeline.h"
#include "OpenGL-basico/pipelines/raster_pipeline.h"
#include "OpenGL-basico/pipelines/viewport_pipeline.h"
#include "OpenGL-basico/solids/cube.h"
#include "OpenGL-basico/solids/sphere.h"

int main(int argc, char* argv[])
{
    // Initialize FreeImage library
    FreeImage_Initialise();

    // Define image dimensions
    constexpr int width = 800;
    constexpr int height = 600;

    const projection_pipeline projection_pipeline(2*3.141590/16, static_cast<float>(width) / height, 0.1, 100);
    const viewport_pipeline view_pipeline(width, height, {width/2, height/2});
    const raster_pipeline raster_pipeline(width, height);

    auto volumes = std::vector<volume*>();

    // volumes.emplace_back(new sphere({400, 300, 100}, 50, {255, 0, 0}));
    volumes.emplace_back(new cube({5, 10, 10}, 15, color(0, 255, 0)));


    const auto scene = ::scene(volumes);
    const auto ndc_projection = projection_pipeline.project(scene);
    // returns coordinates between -1 and 1 for objects in the screen
    const auto screen_projection = view_pipeline.get_viewport_coordinates(ndc_projection);
    // returns coordinates between 0 and width/height for objects in the screen
    const image image = raster_pipeline.rasterize(screen_projection); // rasterizes image to be displayed
    renderer::render_image(image); // renders image to screen

    FreeImage_DeInitialise();

    return 0;
}
