#include "renderer.h"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "FreeImage.h"
#include "../pipelines/image.h"
#include "../raster/rasterer.h"

std::string get_current_timestamp()
{
    const auto now = std::chrono::system_clock::now();

    const std::time_t current_time = std::chrono::system_clock::to_time_t(now);

    std::tm local_time;
    const auto res = localtime_s(&local_time, &current_time);

    if (res != 0)
    {
        std::cerr << "Failed to convert time" << '\n';
        throw std::runtime_error("Failed to convert time");
    }

    std::ostringstream oss;
    oss << std::put_time(&local_time, "%Y%m%d_%H%M%S");

    return oss.str();
}

void renderer::render_image(const image& image)
{
    auto current_time = get_current_timestamp();
    const auto width = image.width;
    const auto height = image.height;

    // Create an empty 24-bit RGB image
    FIBITMAP* bitmap = FreeImage_Allocate(width, height, 24);

    if (!bitmap)
    {
        std::cerr << "Failed to allocate memory for the image\n";
        FreeImage_DeInitialise();
        throw std::runtime_error("Failed to allocate memory for the image");
    }
    RGBQUAD rgb;
    try
    {
        const auto pixels = image.pixels;
        for (pixel pixel : pixels)
        {
            rgb = pixel.color.to_rgb();
            FreeImage_SetPixelColor(bitmap, pixel.point.x, pixel.point.y, &rgb);
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
