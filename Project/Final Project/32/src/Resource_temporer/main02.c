#include <stdio.h>
#include <math.h>
#include "SDL.h"
#include <stdbool.h>

#define FPS 30
#define FRAME_TARGET_TIME (1000 / FPS)
#define MAP_WIDTH 432
#define MAP_HEIGHT 384
#define BOX 48
#define TIMER_WIDTH BOX / 2

int last_frame_time = 0;
int HIEGHT = 9, WIDTH = 10;
bool playing = true;
int Frame = 15;
int timerColor[3][3] = {{223, 243, 208}, {255, 246, 90}, {255, 97, 61}};
int indexTimerColor = 0;

typedef struct
{
    int x, y;
} Position;

struct game_object
{
    Position pos;
    float width;
    float height;
    float vel_x;
    float vel_y;
} ball;

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

SDL_Window *window;
SDL_Renderer *render;
Player Snoppy, S_animated;

Timer GameTimer;
BlockPositions blockMap;

int totaleTime;

// ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

Position GetPlayerPosition();
void SetPlayerPositionTo(int, int);

int IndexToRealPos(int index)
{
    return index * BOX + BOX / 2;
}

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

void drowPlayer();

void SetUp()
{
    // set class of the timer game
    GameTimer.w = WIDTH - 1;
    GameTimer.h = HIEGHT - 1;
    GameTimer.Totale = (GameTimer.w * 2 + GameTimer.h * 2) * 2 - 4;
    GameTimer.dec = 2;
    GameTimer.time = 0.3;

    // set timer for decresing
    totaleTime = GameTimer.time * 500;

    // Tmp Position of Grides
    blockMap.pos = (Position *)calloc(4, sizeof(Position));
    blockMap.nbr = 4;
    blockMap.pos[0].x = 0;
    blockMap.pos[0].y = 6;
    blockMap.pos[1].x = 8;
    blockMap.pos[1].y = 2;
    blockMap.pos[2].x = 3;
    blockMap.pos[2].y = 2;
    blockMap.pos[3].x = 1;
    blockMap.pos[3].y = 3;

    ball.pos.x = MAP_WIDTH / 2;
    ball.pos.y = MAP_HEIGHT / 2;
    ball.width = 24;
    ball.height = 24;
    ball.vel_x = 180;
    ball.vel_y = 140;
    SetPlayerPositionTo(0, 0);
    S_animated.pos.x = Snoppy.pos.x;
    S_animated.pos.y = Snoppy.pos.y;
}

void drawBall()
{
    SDL_Rect ball_rect = {
        (int)ball.pos.x,
        (int)ball.pos.y,
        (int)ball.width,
        (int)ball.height};
    SDL_RenderFillRect(render, &ball_rect);
}

// ...
Position GetPlayerPosition()
{
    Position var;
    var.x = (int)(Snoppy.pos.x - 24) / (BOX);
    var.y = (int)(Snoppy.pos.y - 24) / (BOX);
    return var;
}
// function that take the curent index of player and add the nextX & nextY
void SetPlayerPositionTo(int nextX, int nextY)
{
    if (nextX >= 0 && nextX < WIDTH - 1 && nextY >= 0 && nextY < HIEGHT - 1)
    {
        Snoppy.pos.x = nextX * BOX + (TIMER_WIDTH);
        Snoppy.pos.y = nextY * BOX + (TIMER_WIDTH);
    }
    else
    {
        printf("Can't do a position out of the matrix");
    }
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
            switch (event.key.keysym.sym)
            {
            case SDLK_LEFT:
                SetPlayerPositionTo(GetPlayerPosition().x - 1, GetPlayerPosition().y);
                break;
            case SDLK_RIGHT:
                SetPlayerPositionTo(GetPlayerPosition().x + 1, GetPlayerPosition().y);
                break;
            case SDLK_UP:
                SetPlayerPositionTo(GetPlayerPosition().x, GetPlayerPosition().y - 1);
                break;
            case SDLK_DOWN:
                SetPlayerPositionTo(GetPlayerPosition().x, GetPlayerPosition().y + 1);
                break;
            }
        }
    }
}

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
    SDL_Rect destinationRect = {TIMER_WIDTH, TIMER_WIDTH, BOX * (WIDTH - 1), BOX * (HIEGHT - 1)};
    SDL_RenderCopy(render, texture, NULL, &destinationRect);

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            SDL_SetRenderDrawColor(render, 255, 255, 255, 255); // White color
            SDL_Rect topRect = {(i * (WIDTH * BOX - (TIMER_WIDTH))), (j * (BOX * HIEGHT - (TIMER_WIDTH))), TIMER_WIDTH, TIMER_WIDTH};
            SDL_RenderFillRect(render, &topRect);
        }
    }
    makeTimer();
    RenderMap();
    drowPlayer();
}

void drowPlayer()
{
    SDL_SetRenderDrawColor(render, 255, 0, 255, 255); // White color
    SDL_Rect topRect = {Snoppy.pos.x, Snoppy.pos.y, BOX, BOX};
    SDL_RenderFillRect(render, &topRect);
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
        SDL_Rect topRect = {(i * BOX) + BOX * 4, 0, BOX, TIMER_WIDTH};
        SDL_RenderFillRect(render, &topRect);
    }
    int totaleLeft = GameTimer.Totale;
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
        SDL_Rect topRect = {((i * (TIMER_WIDTH)) + TIMER_WIDTH) + (BOX / 12), 0 + (BOX / 16), TIMER_WIDTH - BOX / 6, TIMER_WIDTH - BOX / 6};
        SDL_RenderFillRect(render, &topRect);
        if (totaleLeft >= 0)
        {
            totaleLeft--;
        }
    }
    for (int i = 0; i < GameTimer.h * 2; i++)
    {
        if (totaleLeft > 0)
        {
            SDL_SetRenderDrawColor(render, timerColor[indexTimerColor][0], timerColor[indexTimerColor][1], timerColor[indexTimerColor][2], 255); // Dark gray color
        }
        else
        {
            SDL_SetRenderDrawColor(render, 52, 98, 88, 255); // Light gray color
        }
        SDL_Rect topRect = {0 + (BOX / 16), ((i * (TIMER_WIDTH)) + TIMER_WIDTH) + (BOX / 12), TIMER_WIDTH - BOX / 6, TIMER_WIDTH - BOX / 6};
        SDL_RenderFillRect(render, &topRect);
        if (totaleLeft >= 0)
        {
            totaleLeft--;
        }
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
        SDL_Rect topRect = {((i * (TIMER_WIDTH)) + TIMER_WIDTH) + (BOX / 12), (BOX * (HIEGHT - 1)) + (TIMER_WIDTH) + (BOX / 16), TIMER_WIDTH - BOX / 6, TIMER_WIDTH - BOX / 6};
        SDL_RenderFillRect(render, &topRect);
        if (totaleLeft >= 0)
        {
            totaleLeft--;
        }
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
        SDL_Rect topRect = {(BOX * (WIDTH - 1)) + (TIMER_WIDTH) + (BOX / 16), ((i * (TIMER_WIDTH)) + TIMER_WIDTH) - (TIMER_WIDTH) + (BOX / 12), TIMER_WIDTH - BOX / 6, TIMER_WIDTH - BOX / 6};
        SDL_RenderFillRect(render, &topRect);
        if (totaleLeft >= 0)
        {
            totaleLeft--;
        }
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
        SDL_Rect topRect = {((5 * BOX + (TIMER_WIDTH)) + (i * (TIMER_WIDTH)) + TIMER_WIDTH) + (BOX / 12), 0 + (BOX / 16), TIMER_WIDTH - BOX / 6, TIMER_WIDTH - BOX / 6};
        SDL_RenderFillRect(render, &topRect);
        if (totaleLeft >= 0)
        {
            totaleLeft--;
        }
    }
}

void GameTimeClock()
{
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

void ballCollision()
{
    float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0;
    last_frame_time = SDL_GetTicks();

    ball.pos.x += ball.vel_x * delta_time;
    ball.pos.y += ball.vel_y * delta_time;

    for (int i = 0; i < blockMap.nbr; i++)
    {
        float boxRight = IndexToRealPos(blockMap.pos[i].x) + BOX;
        float boxBottom = IndexToRealPos(blockMap.pos[i].y) + BOX;

        if (ball.pos.x < boxRight && ball.pos.x + ball.width > IndexToRealPos(blockMap.pos[i].x) && ball.pos.y < boxBottom && ball.pos.y + ball.height > IndexToRealPos(blockMap.pos[i].y))
        {
            float overlapX = fmin(fabs(ball.pos.x + ball.width - IndexToRealPos(blockMap.pos[i].x)), fabs(IndexToRealPos(blockMap.pos[i].x) + BOX - ball.pos.x));
            float overlapY = fmin(fabs(ball.pos.y + ball.height - IndexToRealPos(blockMap.pos[i].y)), fabs(IndexToRealPos(blockMap.pos[i].y) + BOX - ball.pos.y));
            if (overlapX > overlapY)
            {
                ball.pos.y = (ball.vel_y > 0) ? (IndexToRealPos(blockMap.pos[i].y) - ball.height) : (IndexToRealPos(blockMap.pos[i].y) + BOX);
                ball.vel_y = -ball.vel_y;
            }
            else
            {
                ball.pos.x = (ball.vel_x > 0) ? (IndexToRealPos(blockMap.pos[i].x) - ball.width) : (IndexToRealPos(blockMap.pos[i].x) + BOX);
                ball.vel_x = -ball.vel_x;
            }
        }
    }

    if (ball.pos.x < TIMER_WIDTH)
    {
        ball.pos.x = TIMER_WIDTH;
        ball.vel_x = -ball.vel_x;
    }
    if (ball.pos.x + ball.height > MAP_WIDTH + TIMER_WIDTH)
    {
        ball.pos.x = MAP_WIDTH + TIMER_WIDTH - ball.width;
        ball.vel_x = -ball.vel_x;
    }
    if (ball.pos.y < TIMER_WIDTH)
    {
        ball.pos.y = TIMER_WIDTH;
        ball.vel_y = -ball.vel_y;
    }
    if (ball.pos.y + ball.height > MAP_WIDTH - TIMER_WIDTH)
    {
        ball.pos.y = MAP_WIDTH - TIMER_WIDTH - ball.height;
        ball.vel_y = -ball.vel_y;
    }
}

// Render the BOX depending on the index x,y (0 to 8 for X ----- 0 to 7 for Y)
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
        SDL_Rect destinationRect = {(blockMap.pos[i].x * BOX) + TIMER_WIDTH, (blockMap.pos[i].y * BOX) + TIMER_WIDTH, BOX, BOX};
        SDL_RenderCopy(render, texture, NULL, &destinationRect);
    }
}
// ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
void RenderGame()
{
    SDL_RenderClear(render);
    SDL_SetRenderDrawColor(render, 0, 23, 27, 255);
    makeGread();
    drawBall();
    SDL_RenderPresent(render);
}

void Update()
{
    HandelEvents();
    GameTimeClock();
    ballCollision();
}

int main(int argc, char **argv)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        getc(stdin);
        return 1;
    }
    window = SDL_CreateWindow("Simple Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, BOX * WIDTH, HIEGHT * BOX, SDL_WINDOW_SHOWN);
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
        Update();
        RenderGame();
        SDL_Delay(FPS);
    }
    // ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

    // Game End
    EndGame();

    return 0;
}
