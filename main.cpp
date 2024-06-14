#include <iostream>

#include "Freeimage/FreeImage.h"
#include "OpenGL-basico/graphics/renderer.h"
#include "OpenGL-basico/scene/new_scene.h"
#include "OpenGL-basico/xml/scene_parser.h"

int main(int argc, char* argv[])
{
    try
    {
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            std::cerr << "No se pudo iniciar SDL: " << SDL_GetError() << '\n';
            return 1;
        }
        int width = 800;
        int height = 600;
        FreeImage_Initialise();
        SDL_Window* window = SDL_CreateWindow("Renderizado",
                                              SDL_WINDOWPOS_CENTERED,
                                              SDL_WINDOWPOS_CENTERED,
                                              width, height,
                                              SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        new_scene scene = new_scene(width, height, "../scenes/scene_2.xml");
        for (image img : scene.Render(renderer))
        {
            renderer::render_image(img); // renders image to screen
        }

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

            SDL_Delay(2000); // Agregar un retraso de ~16 ms para evitar que el bucle consuma demasiados recursos de CPU
        }

        // Limpia recursos SDL y termina el programa
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        FreeImage_DeInitialise();
        return 0;
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
}
