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

void renderer::render_image(image& image, SDL_Renderer* renderer)
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

    std::cout << "Rendering image." << std::endl;

    render_intermedium_image(image, renderer);
    
}

void renderer::render_intermedium_image(image& img, SDL_Renderer* renderer)
{
    std::cout << "Creating texture from image." << std::endl;
    std::cout << "Image dimensions: " << img.width << "x" << img.height << std::endl;

    if (!renderer)
    {
        std::cerr << "Renderer is invalid." << std::endl;
        return;
    }

    if (img.pixels.empty() || img.width <= 0 || img.height <= 0)
    {
        std::cerr << "Invalid image data." << std::endl;
        return;
    }

    // Crear un buffer para los datos de los píxeles en formato RGBA
    std::vector<uint32_t> pixel_data(img.width * img.height);
    for (int x = 0; x < img.width; x++)
    {
        for (int y = 0; y < img.height; y++)
        {
            pixel& p = img.get_pixel(x, img.height-y);
            color& c = p.color_;
            uint32_t rgba = (static_cast<uint8_t>(c.get_red()) << 24) |
                            (static_cast<uint8_t>(c.get_green()) << 16) |
                            (static_cast<uint8_t>(c.get_blue()) << 8) |
                            static_cast<uint8_t>(c.get_alpha());
            pixel_data[y * img.width + x] = rgba;
        }
    }

    // Crear la superficie SDL desde el buffer de píxeles
    SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(
        pixel_data.data(),
        img.width,
        img.height,
        32, // bits per pixel
        img.width * sizeof(uint32_t), // pitch: bytes per row
        0xFF000000, // Red mask
        0x00FF0000, // Green mask
        0x0000FF00, // Blue mask
        0x000000FF  // Alpha mask
    );

    if (!surface)
    {
        std::cerr << "SDL_CreateRGBSurfaceFrom Error: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture)
    {
        std::cerr << "Failed to create texture from image." << std::endl;
        return;
    }

    SDL_RenderClear(renderer);

    if (SDL_RenderCopy(renderer, texture, NULL, NULL) != 0)
    {
        std::cerr << "SDL_RenderCopy Error: " << SDL_GetError() << std::endl;
    }

    SDL_RenderPresent(renderer);

    SDL_DestroyTexture(texture);
}