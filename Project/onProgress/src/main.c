#include <stdio.h>
#include "SDL.h"
#include <stdbool.h>

typedef struct
{
    int w, h;
    float x, y;
    int lives;
} Player;

typedef struct
{
    int Totale, dec;
} Timer;

// Public variables to make acces more easier
const int WIDTH = 432, box = 48;
bool playing = true;
SDL_Window *window;
SDL_Renderer *render;
Player Snoppy;
Timer GameTimer;

void EndGame()
{
    SDL_RenderClear(render);
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void RenderGame()
{
}

void Update()
{
}

void HandelEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_LEFT)
            {
            }
        }
        else if (event.type == SDL_QUIT)
        {
            EndGame();
        }
    }
}

int main(int argc, char **argv)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        getc(stdin);
        return 1;
    }
    window = SDL_CreateWindow("Simple Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, WIDTH, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        getc(stdin);
        return 1;
    }
    render = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(render, 255, 255, 255, 255);

    if (window == NULL)
    {
        fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        getc(stdin);
        return 1;
    }

    while (playing)
    {
        HandelEvents();
        Update();
        RenderGame();
        SDL_Delay(20);
    }

    EndGame();

    return 0;
}
