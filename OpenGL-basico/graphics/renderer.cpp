#include "renderer.h"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "../scene/scene.h"
#include "FreeImage.h"
#include "../raster/line.h"
#include "../raster/mid_point_algorithm.h"

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
    auto current_time = get_current_timestamp();

    // Create an empty 24-bit RGB image
    FIBITMAP* bitmap = FreeImage_Allocate(width, height, 24);


    auto diagonal = line({0, 0}, {static_cast<float>(width), static_cast<float>(height)});
    auto circle = ::circle({200, 300}, 100);

    auto draw_line = mid_point_algorithm::raster(diagonal);
    auto draw_circle = mid_point_algorithm::raster(circle);

    if (!bitmap)
    {
        std::cerr << "Failed to allocate memory for the image" << std::endl;
        FreeImage_DeInitialise();
        throw std::runtime_error("Failed to allocate memory for the image");
    }

    try
    {
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                RGBQUAD rgb;
                rgb.rgbRed = 0;
                rgb.rgbGreen = 255;
                rgb.rgbBlue = 0;
                FreeImage_SetPixelColor(bitmap, x, y, &rgb);
            }
        }
        for (auto point : draw_line)
        {
            RGBQUAD rgb;
            rgb.rgbRed = 255;
            rgb.rgbGreen = 0;
            rgb.rgbBlue = 0;
            FreeImage_SetPixelColor(bitmap, point.x, point.y, &rgb);
        }
        for (auto point : draw_circle)
        {
            RGBQUAD rgb;
            rgb.rgbRed = 0;
            rgb.rgbGreen = 0;
            rgb.rgbBlue = 255;
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
