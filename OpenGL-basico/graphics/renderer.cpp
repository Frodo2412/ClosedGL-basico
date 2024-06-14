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

void renderer::render_intermedium_image(image& image, SDL_Renderer* renderer) {
    const auto width = image.width;
    const auto height = image.height;

    // Create an empty 24-bit RGB surface
    SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, 24, 0, 0, 0, 0);
    if (!surface) {
        std::cerr << "Failed to create SDL surface: " << SDL_GetError() << std::endl;
        return;
    }

    // Lock the surface
    if (SDL_LockSurface(surface) != 0) {
        std::cerr << "Failed to lock SDL surface: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(surface);
        return;
    }

    // Copy pixel data to the surface
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            pixel currentPixel = image.get_pixel(x, y);
            Uint8* pixelAddr = (Uint8*)surface->pixels + y * surface->pitch + x * 3;
            *(pixelAddr + 0) = currentPixel.color_.get_red();
            *(pixelAddr + 1) = currentPixel.color_.get_green();
            *(pixelAddr + 2) = currentPixel.color_.get_blue();
        }
    }

    // Unlock the surface
    SDL_UnlockSurface(surface);

    // Create a texture from the surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        std::cerr << "Failed to create SDL texture: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(surface);
        return;
    }

    // Copy the texture to the renderer
    SDL_RenderCopy(renderer, texture, NULL, NULL);

    // Present the renderer
    SDL_RenderPresent(renderer);

    // Destroy the texture and surface
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}