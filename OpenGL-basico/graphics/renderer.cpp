#include "renderer.h"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "FreeImage.h"
#include "image.h"

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

void renderer::render_image(image& image)
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
            rgb = pixel.color_.to_rgb();
            FreeImage_SetPixelColor(bitmap, pixel.point.x, pixel.point.y, &rgb);
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Failed to set image pixels: " << e.what() << '\n';
    }

    auto file_name = image.get_type().append(current_time.append(".png").c_str());

    // Save the image as a PNG file
    if (FreeImage_Save(FIF_PNG, bitmap, file_name.c_str(), 0))
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

SDL_Texture* renderer::render_intermedium_image(image& img, SDL_Renderer* renderer)
{
    // Debug: Logs para verificar las dimensiones de la imagen
    std::cout << "Creating texture from image." << std::endl;
    std::cout << "Image dimensions: " << img.width << "x" << img.height << std::endl;

    // Verificar la validez del renderer
    if (!renderer)
    {
        std::cerr << "Renderer is invalid." << std::endl;
        return nullptr;
    }

    // Verificar los datos de píxeles de la imagen
    if (img.pixels.empty() || img.width <= 0 || img.height <= 0)
    {
        std::cerr << "Invalid image data." << std::endl;
        return nullptr;
    }

    // Crear la superficie SDL desde los datos de la imagen
    SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(
        static_cast<void*>(const_cast<pixel*>(img.pixels.data())), img.width, img.height, 32, img.width * sizeof(pixel),
        0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
    if (!surface)
    {
        std::cerr << "SDL_CreateRGBSurfaceFrom Error: " << SDL_GetError() << std::endl;
        return nullptr; // O manejar el error según sea necesario
    }

    // Crear la textura SDL desde la superficie
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface); // Liberar la superficie después de crear la textura

    if (!texture)
    {
        std::cerr << "Error creating texture: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    return texture;
}