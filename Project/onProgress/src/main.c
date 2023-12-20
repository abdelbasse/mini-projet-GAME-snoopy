#include <stdio.h>
#include "SDL.h"
#include <stdbool.h>

typedef struct
{
    int x,y;
}Position;


typedef struct
{
    Position pos;
    int lives;
} Player;

typedef struct
{
    int Totale, dec;
    int h, w;
    float time;
} Timer;

typedef struct
{
   Position *pos; 
}Blocks;


// Public variables to make acces more easier
int box = 48, HIEGHT = 9, WIDTH = 10;
bool playing = true;
SDL_Window *window;
SDL_Renderer *render;
int Frame = 15;
Player Snoppy;
Timer GameTimer;
int totaleTime;

// Main Function
// ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
void EndGame()
{
    SDL_RenderClear(render);
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void makeTimer();

void makeGread();

void GameTimeClock();

void SetUp()
{
    // set class of the timer game
    GameTimer.w = WIDTH - 1;
    GameTimer.h = HIEGHT - 1;
    GameTimer.Totale = (GameTimer.w * 2 + GameTimer.h * 2) * 2 - 1;
    GameTimer.dec = 1;
    GameTimer.time = 1;

    // set timer for decresing
    totaleTime = GameTimer.time * 500;

    //Tmp Position of Grides
}

void RenderGame()
{
    SDL_RenderClear(render);
    SDL_SetRenderDrawColor(render, 0, 23, 27, 255);
    makeGread();
    SDL_RenderPresent(render);
}

void Update()
{
    GameTimeClock();
}

void HandelEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            EndGame();
        }
        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_LEFT)
            {
            }
        }
    }
}
// ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

// Game Extra function
// ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
void makeGread()
{
    SDL_RenderClear(render);
    SDL_Surface *surface = SDL_LoadBMP("../src/grid.bmp");
    if (!surface)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load BMP image: %s", SDL_GetError());
        EndGame();
        return;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(render, surface);
    SDL_FreeSurface(surface);
    if (!texture)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to create texture from surface: %s", SDL_GetError());
        EndGame();
        return;
    }
    SDL_Rect destinationRect = {box / 2, box / 2, box * (WIDTH - 1), box * (HIEGHT - 1)};
    SDL_RenderCopy(render, texture, NULL, &destinationRect);

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            SDL_SetRenderDrawColor(render, 255, 255, 255, 255); // White color
            SDL_Rect topRect = {(i * (WIDTH * box - (box / 2))), (j * (box * HIEGHT - (box / 2))), box / 2, box / 2};
            SDL_RenderFillRect(render, &topRect);
        }
    }
    makeTimer();
}

void makeTimer()
{
    for (int i = 1; i >= 0; i--)
    {
        if (i >= GameTimer.dec)
        {
            SDL_SetRenderDrawColor(render, 40, 40, 40, 255); // Dark gray color
        }
        else
        {
            SDL_SetRenderDrawColor(render, 200, 200, 200, 255); // Light gray color
        }
        SDL_Rect topRect = {(i * box) + box * 4, 0, box, box / 2};
        SDL_RenderFillRect(render, &topRect);
    }
    int totaleLeft = GameTimer.Totale - 3;
    for (int i = 6; i >= 0; i--)
    {
        if (totaleLeft > 0)
        {
            SDL_SetRenderDrawColor(render, 223, 243, 208, 255); // Dark gray color
        }
        else
        {
            SDL_SetRenderDrawColor(render, 52, 98, 88, 255); // Light gray color
        }
        SDL_Rect topRect = {((i * (box / 2)) + box / 2) + (box / 12), 0 + (box / 16), box / 2 - box / 6, box / 2 - box / 6};
        SDL_RenderFillRect(render, &topRect);
        totaleLeft--;
    }
    for (int i = 0; i < GameTimer.h * 2; i++)
    {
        if (totaleLeft < 0)
        {
            SDL_SetRenderDrawColor(render, 52, 98, 88, 255); // Light gray color
        }
        else
        {
            SDL_SetRenderDrawColor(render, 223, 243, 208, 255); // Dark gray color
        }
        SDL_Rect topRect = {0 + (box / 16), ((i * (box / 2)) + box / 2) + (box / 12), box / 2 - box / 6, box / 2 - box / 6};
        SDL_RenderFillRect(render, &topRect);
        totaleLeft--;
    }
    for (int i = 0; i < GameTimer.w * 2; i++)
    {
        if (totaleLeft > 0)
        {
            SDL_SetRenderDrawColor(render, 223, 243, 208, 255); // Dark gray color
        }
        else
        {
            SDL_SetRenderDrawColor(render, 52, 98, 88, 255); // Light gray color
        }
        SDL_Rect topRect = {((i * (box / 2)) + box / 2) + (box / 12), (box * (HIEGHT - 1)) + (box / 2) + (box / 16), box / 2 - box / 6, box / 2 - box / 6};
        SDL_RenderFillRect(render, &topRect);
        totaleLeft--;
    }
    for (int i = GameTimer.h * 2; i > 0; i--)
    {
        if (totaleLeft > 0)
        {
            SDL_SetRenderDrawColor(render, 223, 243, 208, 255); // Dark gray color
        }
        else
        {
            SDL_SetRenderDrawColor(render, 52, 98, 88, 255); // Light gray color
        }
        SDL_Rect topRect = {(box * (WIDTH - 1)) + (box / 2) + (box / 16), ((i * (box / 2)) + box / 2) - (box / 2) + (box / 12), box / 2 - box / 6, box / 2 - box / 6};
        SDL_RenderFillRect(render, &topRect);
        totaleLeft--;
    }
    for (int i = 6; i >= 0; i--)
    {
        if (totaleLeft > 0)
        {
            SDL_SetRenderDrawColor(render, 223, 243, 208, 255); // Dark gray color
        }
        else
        {
            SDL_SetRenderDrawColor(render, 52, 98, 88, 255); // Light gray color
        }
        SDL_Rect topRect = {((5 * box + (box / 2)) + (i * (box / 2)) + box / 2) + (box / 12), 0 + (box / 16), box / 2 - box / 6, box / 2 - box / 6};
        SDL_RenderFillRect(render, &topRect);
        totaleLeft--;
    }
}

void GameTimeClock()
{
    printf("\n\n ==> %d", totaleTime);
    if (totaleTime < 0)
    {
        GameTimer.Totale -= GameTimer.dec;
        totaleTime = GameTimer.time * 500;
    }
    else
    {
        totaleTime -= Frame;
    }
}

// ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

int main(int argc, char **argv)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        getc(stdin);
        return 1;
    }
    window = SDL_CreateWindow("Simple Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, box * WIDTH, HIEGHT * box, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    render = SDL_CreateRenderer(window, -1, 0);
    if (window == NULL)
    {
        fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    // Set UP
    // ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
    SetUp();
    // ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

    // Game Loop
    //  ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
    while (playing)
    {
        HandelEvents();
        Update();
        RenderGame();
        SDL_Delay(Frame);
    }
    // ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

    // Game End
    EndGame();

    return 0;
}
