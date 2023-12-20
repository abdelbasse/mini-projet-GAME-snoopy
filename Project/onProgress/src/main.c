#include <stdio.h>
#include "SDL.h"
#include <stdbool.h>

const int WIDTH = 340, HIEGHT = 340;
bool playing = true;

void HandelEvents(SDL_Window *window)
{
    SDL_Event event;              // Declare an actual SDL_Event variable
    while (SDL_PollEvent(&event)) // Pass the address of the event variable
    {
        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_LEFT)
        }
    }
}

void RenderGame(SDL_Renderer *render)
{
}

void Update()
{
}

void EndGame(SDL_Window *window, SDL_Renderer *render)
{
    SDL_RenderClear(render);
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char **argv)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        getc(stdin);
        return 1;
    }
    SDL_Window *window = SDL_CreateWindow("Simple Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HIEGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        getc(stdin);
        return 1;
    }
    SDL_Renderer *render = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(render, 255, 255, 255, 255);

    if (window == NULL)
    {
        fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        getc(stdin);
        return 1;
    }

    while (playing)
    {
        Update();
        RenderGame(render);
        SDL_Delay(20);
    }

    EndGame(window, render);

    return 0;
}
