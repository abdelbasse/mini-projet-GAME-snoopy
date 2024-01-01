#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
SDL_Texture *gDigitTexture0 = NULL;
SDL_Texture *gDigitTexture1 = NULL;
SDL_Texture *gDigitTexture2 = NULL;
SDL_Texture *gDigitTexture3 = NULL;
SDL_Texture *gDigitTexture4 = NULL;
SDL_Texture *gDigitTexture5 = NULL;
SDL_Texture *gDigitTexture6 = NULL;
SDL_Texture *gDigitTexture7 = NULL;
SDL_Texture *gDigitTexture8 = NULL;
SDL_Texture *gDigitTexture9 = NULL;

// Function to initialize SDL and load digit textures
int init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "SDL initialization failed. SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    gWindow = SDL_CreateWindow("Score Display", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL)
    {
        fprintf(stderr, "Window creation failed. SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == NULL)
    {
        fprintf(stderr, "Renderer creation failed. SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    // Load digit textures
    gDigitTexture0 = SDL_CreateTextureFromSurface(gRenderer, SDL_LoadBMP("../src/numbers/digit0.bmp"));
    gDigitTexture1 = SDL_CreateTextureFromSurface(gRenderer, SDL_LoadBMP("../src/numbers/digit1.bmp"));
    gDigitTexture2 = SDL_CreateTextureFromSurface(gRenderer, SDL_LoadBMP("../src/numbers/digit2.bmp"));
    gDigitTexture3 = SDL_CreateTextureFromSurface(gRenderer, SDL_LoadBMP("../src/numbers/digit3.bmp"));
    gDigitTexture4 = SDL_CreateTextureFromSurface(gRenderer, SDL_LoadBMP("../src/numbers/digit4.bmp"));
    gDigitTexture5 = SDL_CreateTextureFromSurface(gRenderer, SDL_LoadBMP("../src/numbers/digit5.bmp"));
    gDigitTexture6 = SDL_CreateTextureFromSurface(gRenderer, SDL_LoadBMP("../src/numbers/digit6.bmp"));
    gDigitTexture7 = SDL_CreateTextureFromSurface(gRenderer, SDL_LoadBMP("../src/numbers/digit7.bmp"));
    gDigitTexture8 = SDL_CreateTextureFromSurface(gRenderer, SDL_LoadBMP("../src/numbers/digit8.bmp"));
    gDigitTexture9 = SDL_CreateTextureFromSurface(gRenderer, SDL_LoadBMP("../src/numbers/digit9.bmp"));

    if (gDigitTexture0 == NULL || gDigitTexture1 == NULL || gDigitTexture2 == NULL ||
        gDigitTexture3 == NULL || gDigitTexture4 == NULL || gDigitTexture5 == NULL ||
        gDigitTexture6 == NULL || gDigitTexture7 == NULL || gDigitTexture8 == NULL || gDigitTexture9 == NULL)
    {
        return 0;
    }

    return 1;
}

// Function to render the score
void renderDigit(int digit, int x, int y)
{
    SDL_Texture *digitTexture = NULL;
    switch (digit)
    {
    case 0:
        digitTexture = gDigitTexture0;
        break;
    case 1:
        digitTexture = gDigitTexture1;
        break;
    case 2:
        digitTexture = gDigitTexture2;
        break;
    case 3:
        digitTexture = gDigitTexture3;
        break;
    case 4:
        digitTexture = gDigitTexture4;
        break;
    case 5:
        digitTexture = gDigitTexture5;
        break;
    case 6:
        digitTexture = gDigitTexture6;
        break;
    case 7:
        digitTexture = gDigitTexture7;
        break;
    case 8:
        digitTexture = gDigitTexture8;
        break;
    case 9:
        digitTexture = gDigitTexture9;
        break;
    default:
        // Handle error or default case
        break;
    }

    SDL_Rect destRect = {x, y, 30, 50}; // Adjust the destination rectangle for centering
    SDL_RenderCopy(gRenderer, digitTexture, NULL, &destRect);
}

//  Function to render the score
void renderScore(int score, int nbrDigit, int org_x, int org_y)
{
    char scoreStr[10];
    int x = org_x;
    for (int i = nbrDigit; i > 0; i--)
    {
        int digitIndex = score % 10;
        renderDigit(digitIndex, x, org_y);
        x -= 50; // Adjust the spacing between digits
        score /= 10;
    }
}
// Function to close SDL and free resources
void close()
{
    SDL_DestroyTexture(gDigitTexture0);
    SDL_DestroyTexture(gDigitTexture1);
    SDL_DestroyTexture(gDigitTexture2);
    SDL_DestroyTexture(gDigitTexture3);
    SDL_DestroyTexture(gDigitTexture4);
    SDL_DestroyTexture(gDigitTexture5);
    SDL_DestroyTexture(gDigitTexture6);
    SDL_DestroyTexture(gDigitTexture7);
    SDL_DestroyTexture(gDigitTexture8);
    SDL_DestroyTexture(gDigitTexture9);

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}

int main(int argc, char *args[])
{
    if (!init())
    {
        fprintf(stderr, "Initialization failed. Exiting...\n");
        return 1;
    }

    int quit = 0;
    SDL_Event e;
    int index = 0;
    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = 1;
            }
        }

        SDL_SetRenderDrawColor(gRenderer, 0, 0, 255, 255); // Set background color
        SDL_RenderClear(gRenderer);
        // renderScore(99999);
        SDL_RenderPresent(gRenderer);
        // Introduce a delay between frames
        SDL_Delay(100); // Adjust the delay time as needed
        index++;
        if (index > 9999)
        {
            index = 0;
        }
    }

    close();

    return 0;
}
