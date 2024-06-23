#include <iostream>
#include "Freeimage/FreeImage.h"
#include "OpenGL-basico/graphics/renderer.h"
#include "OpenGL-basico/scene/new_scene.h"
#include "OpenGL-basico/xml/scene_parser.h"

int main(int argc, char* argv[])
{
    try
    {

        new_scene scene("../scenes/scene1.xml");
        std::cout << "Scene loaded successfully.\n";
        
        // Initialize SDL
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            std::cerr << "No se pudo iniciar SDL: " << SDL_GetError() << '\n';
            return 1;
        }
        std::cout << "SDL Initialized successfully.\n";

        // Initialize FreeImage
        FreeImage_Initialise();
        std::cout << "FreeImage Initialized successfully.\n";

        // Create SDL Window
        SDL_Window* window = SDL_CreateWindow("Renderizado",
                                              SDL_WINDOWPOS_CENTERED,
                                              SDL_WINDOWPOS_CENTERED,
                                              scene.get_width(), scene.get_height(),
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
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black color
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer); // Present the black screen
        std::cout << "SDL Renderer created successfully.\n";


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
            
            if (!scene.is_finished())
            {
                // Renderiza la escena y la imagen intermedia
                scene.Render(renderer, 1);
                renderer::render_intermedium_image(scene.get_normal_image(), scene.get_iter(), renderer);
            }
            else
            {
                
                renderer::render_image(scene.get_normal_image());
                renderer::render_image(scene.get_reflectivity_image());
                renderer::render_image(scene.get_refractivity_image());
                quit = true;
            }
            SDL_RenderPresent(renderer);
            //SDL_Delay(5000);
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