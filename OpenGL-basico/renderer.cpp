#include "renderer.h"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "FreeImage.h"

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

void renderer::render_image(const int width, const int height)
{
    auto current_time = get_current_timestamp();

    // Create an empty 24-bit RGB image
    FIBITMAP* bitmap = FreeImage_Allocate(width, height, 24);

    if (!bitmap)
    {
        std::cerr << "Failed to allocate memory for the image" << std::endl;
        FreeImage_DeInitialise();
        throw std::runtime_error("Failed to allocate memory for the image");
    }

    // Set image pixels to a gradient from black to white
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            BYTE color = (BYTE)(255 * x / width); // Gradient from black to white
            RGBQUAD rgb;
            rgb.rgbRed = color;
            rgb.rgbGreen = color;
            rgb.rgbBlue = color;
            FreeImage_SetPixelColor(bitmap, x, y, &rgb);
        }
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
