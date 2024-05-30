#include <iostream>

#include "Freeimage/FreeImage.h"
#include "OpenGL-basico/graphics/renderer.h"
#include "OpenGL-basico/pipelines/projection_pipeline.h"
#include "OpenGL-basico/pipelines/raster_pipeline.h"
#include "OpenGL-basico/solids/cube.h"
#include "OpenGL-basico/solids/sphere.h"

int main(int argc, char* argv[])
{
    // Initialize FreeImage library
    FreeImage_Initialise();

    // Define image dimensions
    constexpr int width = 800;
    constexpr int height = 600;

    const projection_pipeline projection_pipeline(90, static_cast<float>(width) / height, -100.0f, 1000.0f);
    const raster_pipeline raster_pipeline(width, height);

    auto volumes = std::vector<volume*>();

    // volumes.emplace_back(new sphere({400, 300, 100}, 50, {255, 0, 0}));
    volumes.emplace_back(new cube({400, 300, -1}, 100, color(0, 255, 0)));


    const auto scene = ::scene(volumes);
    const auto projection = projection_pipeline.project(scene);
    const image image = raster_pipeline.rasterize(projection);

    renderer::render_image(image);

    FreeImage_DeInitialise();

    return 0;
}
