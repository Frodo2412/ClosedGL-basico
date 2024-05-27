#include "renderer.h"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "../scene/scene.h"
#include "FreeImage.h"
#include "../raster/line.h"
#include "../raster/mid_point_algorithm.h"
#include "../raster/projection.h"
#include "../raster/rasterer.h"
#include "../transformations/viewport.h"
#include "../transformations/view.h"
#include "../transformations/perspective.h"

std::string get_current_timestamp()
{
    // Get the current time as a time_point
    const auto now = std::chrono::system_clock::now();

    // Convert the time_point to a time_t, which represents the calendar time
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    // Convert the time_t to a tm structure for local time using localtime_s
    std::tm local_time;
    const auto res = localtime_s(&local_time, &currentTime);

    if (res != 0)
    {
        std::cerr << "Failed to convert time" << '\n';
        throw std::runtime_error("Failed to convert time");
    }

    // Create a string stream to format the time as a string
    std::ostringstream oss;
    oss << std::put_time(&local_time, "%Y%m%d_%H%M%S");

    // Return the formatted string
    return oss.str();
}

void renderer::render_image(int width, int height, scene scene)
{   
    
    // creo las transfomraciones

    view * view_transformation = new view(scene.get_camera());
    perspective * perspective_transformation = new perspective(2* 3.141590 / 8, 800/600, 0.1, 100);
    viewport * viewport_transformation = new viewport(800, 600, point(0, 0));
    auto current_time = get_current_timestamp();

    // Create an empty 24-bit RGB image
    FIBITMAP* bitmap = FreeImage_Allocate(width, height, 24);

    const auto triangle = polygon({{100, 100}, {200, 200}, {300, 100}}, color(255, 0, 0, 255));
    const auto square = polygon({{50, 50}, {50, 150}, {150, 150}, {150, 50}}, color(0, 0, 255, 255));

    const auto polygons = projection(width, height, {triangle, square});
    auto circle = ::circle({200, 300}, 100);

    // auto rasterer = ::rasterer(color(0, 255, 0, 255));
    //
    // try
    // {
    //     const auto image = rasterer.rasterize(polygons);
    // }
    // catch (const std::exception& e)
    // {
    //     std::cerr << "Failed to rasterize image: " << e.what() << '\n';
    // }
    auto draw_circle = rasterer::rasterize(circle, true);
    
    if (!bitmap)
    {
        std::cerr << "Failed to allocate memory for the image\n";
        FreeImage_DeInitialise();
        throw std::runtime_error("Failed to allocate memory for the image");
    }
    RGBQUAD rgb;
    try
    {
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                rgb.rgbRed = 0;
                rgb.rgbGreen = 0;
                rgb.rgbBlue = 0;
                FreeImage_SetPixelColor(bitmap, x, y, &rgb);
            }
        }
        for (const auto& polygon : polygons.shapes)
        {
            for (auto line : polygon.get_lines())
            {
                auto draw = rasterer::rasterize(line);
                for (auto point : draw)
                {
                    rgb = polygon.fill_color.to_rgb();
                    FreeImage_SetPixelColor(bitmap, point.x, point.y, &rgb);
                }
            }
        }
        for (point point : draw_circle)
        {
            rgb.rgbRed = 255;
            rgb.rgbGreen = 0;
            rgb.rgbBlue = 0;
            FreeImage_SetPixelColor(bitmap, point.x, point.y, &rgb);
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Failed to set image pixels: " << e.what() << '\n';
    }

    const auto file_name = current_time.append(".png").c_str();

    // Save the image as a PNG file
    if (FreeImage_Save(FIF_PNG, bitmap, file_name, 0))
    {
        std::cout << "Image successfully saved to 'output.png'" << '\n';
    }
    else
    {
        std::cerr << "Failed to save image" << '\n';
    }

    // Unload the image and deinitialize the library
    FreeImage_Unload(bitmap);
}
