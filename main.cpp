#include <iostream>
#include "Freeimage/FreeImage.h"
#include "OpenGL-basico/graphics/renderer.h"
#include "OpenGL-basico/scene/new_scene.h"
#include "OpenGL-basico/xml/scene_parser.h"

int main(int argc, char* argv[])
{
    try
    {
        // Initialize SDL
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            std::cerr << "No se pudo iniciar SDL: " << SDL_GetError() << '\n';
            return 1;
        }
        std::cout << "SDL Initialized successfully.\n";

        int width = 800;
        int height = 600;

        // Initialize FreeImage
        FreeImage_Initialise();
        std::cout << "FreeImage Initialized successfully.\n";

        // Create SDL Window
        SDL_Window* window = SDL_CreateWindow("Renderizado",
                                              SDL_WINDOWPOS_CENTERED,
                                              SDL_WINDOWPOS_CENTERED,
                                              width, height,
                                              SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
        if (!window)
        {
            std::cerr << "No se pudo crear la ventana: " << SDL_GetError() << '\n';
            FreeImage_DeInitialise();
            SDL_Quit();
            return 2;
        }
        std::cout << "SDL Window created successfully.\n";

        // Create SDL Renderer
        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (!renderer)
        {
            std::cerr << "No se pudo crear el renderer: " << SDL_GetError() << '\n';
            SDL_DestroyWindow(window);
            FreeImage_DeInitialise();
            SDL_Quit();
            return 3;
        }
        std::cout << "SDL Renderer created successfully.\n";

        new_scene scene(width, height, "../scenes/scene_2.xml");
        std::cout << "Scene loaded successfully.\n";

        for (image img : scene.Render(window, renderer))
        {
            renderer::render_image(img, renderer); // renders image to screen
            SDL_Delay(2000);
        }
        std::cout << "Scene rendered successfully.\n";
        
        SDL_Event e;
        bool quit = false;
        while (!quit)
        {
            while (SDL_PollEvent(&e))
            {
                if (e.type == SDL_QUIT)
                {
                    quit = true;
                }
            }
        }
        
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        FreeImage_DeInitialise();
        std::cout << "Resources cleaned up and program terminated successfully.\n";
        return 0;
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
}
