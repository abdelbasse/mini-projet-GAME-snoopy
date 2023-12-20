#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"
#include <stdbool.h>

const int WIDTH = 640, HEIGHT = 640;
bool stillPlaying = true;

typedef struct
{
    int w, h;
    float x, y;
} Player;

void PlayerMove(Player *player, int dir)
{
    if (dir == 1)
    {
        if (!((WIDTH - (player->x) > WIDTH - player->w)))
            player->x -= player->w;
    }
    else if (dir == 2)
    {
        if (!((WIDTH) - (player->x + (player->w)) < 1))
            player->x += player->w;
    }
    else if (dir == 3)
    {
        if (!((HEIGHT) - (player->y) > HEIGHT - player->h))
            player->y -= player->h;
    }
    else if (dir == 4)
    {
        if (!((HEIGHT) - (player->y + (player->h)) < 1))
            player->y += player->h;
    }
}

void EndGame(SDL_Window *window, SDL_Renderer *render)
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(render);
    SDL_Quit();
}

void Update(Player *player)
{
}

void HandelEvents(SDL_Renderer *render, SDL_Window *window, Player *player)
{
    SDL_Event event;              // Declare an actual SDL_Event variable
    while (SDL_PollEvent(&event)) // Pass the address of the event variable
    {
        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_LEFT)
            {
                PlayerMove(player, 1);
            }
            else if (event.key.keysym.sym == SDLK_RIGHT)
            {
                PlayerMove(player, 2);
            }
            else if (event.key.keysym.sym == SDLK_UP)
            {
                PlayerMove(player, 3);
            }
            else if (event.key.keysym.sym == SDLK_DOWN)
            {
                PlayerMove(player, 4);
            }
        }
        else if (event.type == SDL_QUIT)
        {
            EndGame(window, render); // Set the running flag to false to exit the loop
        }
    }
}

void RenderScreen(SDL_Renderer *render, Player *player)
{
    SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
    SDL_RenderClear(render);

    SDL_SetRenderDrawColor(render, 0, 0, 0, 255); // Set color for the player
    SDL_Rect playerRect = {player->x - player->w / 2, player->y - player->h / 2, player->w, player->h};
    SDL_RenderFillRect(render, &playerRect);

    SDL_RenderPresent(render);
}

void ShowInTerminal(Player *player)
{
    printf("Player size ( w:%d , h:%d ) position [ x:%f , y:%f ] \n\n", player->w, player->h, player->x, player->y);
}

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("Snoppy", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *render = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
    Player player;
    player.h = 30;
    player.w = 30;
    player.x = WIDTH / 2;
    player.y = HEIGHT / 2;
    bool running = true;
    while (running)
    {
        HandelEvents(render, window, &player);
        Update(&player);
        RenderScreen(render, &player);
        SDL_Delay(16);
        if (running == false)
        {
            break;
        }
        ShowInTerminal(&player);
    }

    printf("\nEnd of the game!!\n\n");
    EndGame(window, render);
    getc(stdin);
    return 0;
}
