#include "renderer.h"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

#include "../scene/scene.h"
#include "FreeImage.h"
#include "../geometry/line.h"
#include "../transformations/perspective.h"
#include "../transformations/view.h"

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

    auto line = ::line({0, 0, 0}, {static_cast<float>(width), static_cast<float>(height), 0});

    const auto camera = scene.get_camera();

    const auto fov = camera.get_fov();
    const auto aspect_ratio = static_cast<float>(width) / static_cast<float>(height);
    const auto near = camera.get_near();
    const auto far = camera.get_far();

    const ::transformation transformation = view(scene.get_camera());

    const ::line new_line = ::line(transformation.transform(line.get_start()),
                                   transformation.transform(line.get_end()));

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
                if (new_line.is_in_path({static_cast<float>(x), static_cast<float>(y), 0}))
                {
                    RGBQUAD rgb;
                    rgb.rgbRed = 255;
                    rgb.rgbGreen = 0;
                    rgb.rgbBlue = 0;
                    FreeImage_SetPixelColor(bitmap, x, y, &rgb);
                }
                else
                {
                    RGBQUAD rgb;
                    rgb.rgbRed = 0;
                    rgb.rgbGreen = 255;
                    rgb.rgbBlue = 0;
                    FreeImage_SetPixelColor(bitmap, x, y, &rgb);
                }
            }
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
