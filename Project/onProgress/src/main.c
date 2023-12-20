#include <stdio.h>
#include "SDL.h"
#include <stdbool.h>

typedef struct
{
    int x, y;
} Position;

typedef struct
{
    Position pos;
    int lives;
    int lastDirection;
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
    int nbr;
} BlockPositions;

// Public variables to make acces more easier
int box = 48, HIEGHT = 9, WIDTH = 10;
bool playing = true;
int Frame = 15;
int timerColor[3][3] = {{223, 243, 208}, {255, 246, 90}, {255, 97, 61}};
int indexTimerColor = 0;

SDL_Window *window;
SDL_Renderer *render;
Player Snoppy;
Timer GameTimer;
BlockPositions blockMap;

int totaleTime;

// ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

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

void RenderMap();

void GameTimeClock();

void SetUp()
{
    // set class of the timer game
    GameTimer.w = WIDTH - 1;
    GameTimer.h = HIEGHT - 1;
    GameTimer.Totale = (GameTimer.w * 2 + GameTimer.h * 2) * 2 - 4;
    GameTimer.dec = 1;
    GameTimer.time = 1;

    // set timer for decresing
    totaleTime = GameTimer.time * 500;

    // Tmp Position of Grides
    blockMap.pos = (Position *)calloc(4, sizeof(Position));
    blockMap.nbr = 4;
    blockMap.pos[0].x = 1;
    blockMap.pos[0].y = 0;
    blockMap.pos[1].x = 8;
    blockMap.pos[1].y = 3;
    blockMap.pos[2].x = 3;
    blockMap.pos[2].y = 7;
    blockMap.pos[3].x = 6;
    blockMap.pos[3].y = 3;
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
    RenderMap();
}

void makeTimer()
{
    SDL_RenderClear(render);
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
    int totaleLeft = GameTimer.Totale - 4;
    printf("\n\t===> tail : %d", GameTimer.Totale);
    if (totaleLeft < ((2 * 64) / 3))
    {
        indexTimerColor = 1;
    }
    if (totaleLeft < (64 / 3))
    {
        indexTimerColor = 2;
    }
    for (int i = 6; i >= 0; i--)
    {
        if (totaleLeft > 0)
        {
            SDL_SetRenderDrawColor(render, timerColor[indexTimerColor][0], timerColor[indexTimerColor][1], timerColor[indexTimerColor][2], 255); // Dark gray color
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
            SDL_SetRenderDrawColor(render, timerColor[indexTimerColor][0], timerColor[indexTimerColor][1], timerColor[indexTimerColor][2], 255); // Dark gray color
        }
        SDL_Rect topRect = {0 + (box / 16), ((i * (box / 2)) + box / 2) + (box / 12), box / 2 - box / 6, box / 2 - box / 6};
        SDL_RenderFillRect(render, &topRect);
        totaleLeft--;
    }
    for (int i = 0; i < GameTimer.w * 2; i++)
    {
        if (totaleLeft > 0)
        {
            SDL_SetRenderDrawColor(render, timerColor[indexTimerColor][0], timerColor[indexTimerColor][1], timerColor[indexTimerColor][2], 255); // Dark gray color
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
            SDL_SetRenderDrawColor(render, timerColor[indexTimerColor][0], timerColor[indexTimerColor][1], timerColor[indexTimerColor][2], 255); // Dark gray color
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
            SDL_SetRenderDrawColor(render, timerColor[indexTimerColor][0], timerColor[indexTimerColor][1], timerColor[indexTimerColor][2], 255); // Dark gray color
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

// Render the box depending on the index x,y (0 to 8 for X ----- 0 to 7 for Y)
void RenderMap()
{
    for (int i = 0; i < blockMap.nbr; i++)
    {
        SDL_Surface *surface = SDL_LoadBMP("../src/block.bmp");
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
        SDL_Rect destinationRect = {(blockMap.pos[i].x * box) + box / 2, (blockMap.pos[i].y * box) + box / 2, box, box};
        SDL_RenderCopy(render, texture, NULL, &destinationRect);
    }
}

Position GetPlayerPosition()
{
    Position var;
    var.x = Snoppy.pos.x * box + (box / 2);
    var.y = Snoppy.pos.y * box + (box / 2);
    return var;
}
// function that take the curent index of player and add the nextX & nextY
void SetPlayerPositionTo(int nextX, int nectY)
{
    // Code that chnage the icon of player depeding on the direction using(.lastDirection in  structer)
    //
    //  code Chnage the x and y
    Snoppy;
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
