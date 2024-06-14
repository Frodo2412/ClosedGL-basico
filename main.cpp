#include <iostream>

#include "Freeimage/FreeImage.h"
#include "OpenGL-basico/graphics/renderer.h"
#include "OpenGL-basico/scene/new_scene.h"
#include "OpenGL-basico/xml/scene_parser.h"
#include <SDL.h>

int initSDL(SDL_Window* window, SDL_Renderer* renderer, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Error: No se pudo inicializar SDL. " << SDL_GetError() << std::endl;
        return -1;
    }

    window = SDL_CreateWindow("Textura con SDL y FreeImage", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Error: No se pudo crear la ventana. " << SDL_GetError() << std::endl;
        return -1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Error: No se pudo crear el renderer. " << SDL_GetError() << std::endl;
        return -1;
    }

    auto texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);

    if (!texture) {
        std::cerr << "Texture could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        return false;
    }

    return 0;
}

void render_to_sdl(SDL_Renderer* renderer, SDL_Texture* texture, const std::vector<Uint32>& pixelBuffer, int width, int height) {
    void* pixels;
    int pitch;
    SDL_LockTexture(texture, NULL, &pixels, &pitch);

    Uint32* dst = (Uint32*)pixels;
    std::memcpy(dst, pixelBuffer.data(), width * height * sizeof(Uint32));

    SDL_UnlockTexture(texture);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}


int main(int argc, char* argv[])
{
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Texture* textura = nullptr;
    int width = 800;
    int height = 600;
    if (initSDL(window, renderer, width, height) != 0) {
        std::cerr << "Error: No se pudo inicializar SDL." << std::endl;
        return -1;
    }
    try
    {
        FreeImage_Initialise();
        int width = 800;
        int height = 600;

        new_scene scene = new_scene(width, height, "../scenes/scene_2.xml", window, renderer, textura);
        auto images = scene.Render();
        for(image img : images)
        {
            renderer::render_image(img); // renders image to screen
        }

        // Renderiza la primera imagen (normal) a SDL
        if (!images.empty()) {
            image& img = images[0];
            render_to_sdl(renderer, textura, img.get_pixel_data(), img.get_width(), img.get_height());
        }

        FreeImage_DeInitialise();
        
        // Espera a que el usuario cierre la ventana
        SDL_Event e;
        bool quit = false;
        while (!quit) {
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                }
            }
        }

        SDL_DestroyTexture(textura);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        
        return 0;
    } catch (std::exception& e) {
        std::cerr << e.what() << '\n';
        return 1;
    }
}
