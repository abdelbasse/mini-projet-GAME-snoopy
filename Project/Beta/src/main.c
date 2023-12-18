#include <stdio.h>
#include "SDL.h"

int main(int argc, char **argv)
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create a window
    SDL_Window *window = SDL_CreateWindow("Simple Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Delay to show the window for a short period (in milliseconds)
    SDL_Delay(200000000);

    // Destroy the window
    SDL_DestroyWindow(window);

    // Quit SDL
    SDL_Quit();

    return 0;
}
