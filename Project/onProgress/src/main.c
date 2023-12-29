#include <stdio.h>
#include "SDL.h"
#include <math.h>
#include <stdbool.h>
#include <string.h>

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

// add structure presnete un LEVEL (is tmp [stll can add modification])
typedef struct
{
    char *urlFile;
    bool isOpen;
} Level;

// Add Structure contain the list of player LeveL and current level Reached by the player using XML file
typedef struct
{
    Level *list;
    int nbr;
} Levels;

// Astructure presenat the sprite for animation the snoppy in menu
typedef struct
{
    Position pos;
    int width, height, frameWidth, frameHeight, rows, cols;
    int currentFrame;
    float TimePerFrame;
    float curentTimeLeft;
    SDL_Surface *surface;
    SDL_Texture *texture;
} Sprite;

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

// Menu have 2 snoppy the bad and the good one , here the vaeiables
Sprite SnoopyMain, BadSnoppyMain;

SDL_Window *window;
SDL_Renderer *render;
Player Snoppy;
Timer GameTimer;
BlockPositions blockMap;

int totaleTime;

SDL_Surface *playerUpSurface;
SDL_Surface *playerDownSurface;
SDL_Surface *playerLeftSurface;
SDL_Surface *playerRightSurface;
// Add ActionSurface (the cursore allow user for selection options)
SDL_Surface *ActionSurface;

// Declare player texture variables globally
SDL_Texture *playerUpTexture;
SDL_Texture *playerDownTexture;
SDL_Texture *playerLeftTexture;
SDL_Texture *playerRightTexture;
// Add ActionTexture (the cursore allow user for selection options)
SDL_Texture *ActionTexture;

// Player structure Levels Variable so we can use it
Levels PlayerLevels;

// ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// Very importent variable conataine the index of layer selection [note that we use this cursore for pause and menu and select levels]
int ActionPointer = 0;
// ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

// And Array of position For curesure Render Pause
Position PauseActionPointerPositions[2] = {
    {90, 182},
    {90, 230}};
bool Paused = false;

// And Array of position For curesure Render Menu
Position MenuPlayActionPointerPositions[3] = {
    {100, 255},
    {100, 297},
    {100, 340}};

// Very imortant varibake indicate if the game is in the [Menu] or in the [GamePlay]
bool PlayerInMenu = true;

// And Array of position For curesure Render Menu LEVELS Obtions
Position LevelMenuPlayActionPointerPositions[7] = {
    {100, 35},
    {100, 89},
    {100, 137},
    {100, 184},
    {100, 231},
    {100, 278},
    {100, 325}};

int ObtionSousMenu = 0;
//
// 0 : mean it a normal menu have the 3 obtion
// 1 : indicate that the user selected the first option
// 2 : indicate user select to see the LEVELS list
// 3 : see The Scores
// menu home tretement

Position GetPlayerPosition();
void SetPlayerPositionTo(int, int);
void EndGame();
void makeTimer();
void makeGrid();
// Functin make the render of Menu
void makeMenu();
void RenderMap();
void GameTimeClock();
void drawPlayer();
void SetUp();
void drawBall();
// Functin make the render of Cursure Depending on the position
void drawCurserAction(Position);
// Function called in the HandelEvent for gestion Pause Events [click : "ESQ" ]
void PauseEvents(SDL_Event);
// Function called in the HandelEvent for to Handel the selecion of the obtion of the player
void Menu_1_Events(SDL_Event);
// Function called in the HandelEvent for to Handel the selecion of the obtion of the player in LEVELS MENU
void ListMenuEventsSelect(SDL_Event);
// Function called in the REnderGame to Render Our Pause Function and keep a blury wiht opacity background
void PauseGameRender();
bool CheckCollision(Position a, Position b, float width, float height);
bool CheckBlockCollision(Position nextPosition);
void SetPlayerPositionTo(int nextX, int nextY);
int IndexToRealPos(int index);
void ballCollision();
// Function that change do the animation and the movement of the Snoppy in Menu ( just additionel function u want fint it useful)
void SpriteUpdateAnimation(Sprite *);
// Function that Render our LEVELS obtions with order plus the obtion of the Reurn to Exit [non of the levels work]
void RenderLevelsMenu();
// Function that render our Sprite
void drawSprite(Sprite *);

// ========================= devide the update to 2 function to make things more easier to modife =========================================
// a function is the update but only but the element needed for the gameplay like score ect
void GamePlayUpdate();
// a function is the update but only but the element needed for the Menu Tretemtn
void MenuUpdate();

// ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
void HandelEvents();
void RenderGame();
void Update();
// ||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

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
    SetUp();
    while (playing)
    {
        Update();
        RenderGame();
        SDL_Delay(15);
    }
    EndGame();
    return 0;
}

void EndGame()
{
    playing = false;
    for (int i = 0; i < PlayerLevels.nbr; i++)
    {
        free(PlayerLevels.list[0].urlFile);
    }
    free(PlayerLevels.list);
    SDL_RenderClear(render);
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void SetUp()
{
    playerUpSurface = SDL_LoadBMP("../src/Snoppy/Snoppy-up.bmp");
    playerDownSurface = SDL_LoadBMP("../src/Snoppy/Snoppy-down.bmp");
    playerLeftSurface = SDL_LoadBMP("../src/Snoppy/Snoppy-left.bmp");
    playerRightSurface = SDL_LoadBMP("../src/Snoppy/Snoppy-right.bmp");
    ActionSurface = SDL_LoadBMP("../src/actionPointer.bmp");

    // Smoppy show in the menu
    SnoopyMain.frameWidth = 287;
    SnoopyMain.frameHeight = 385;
    SnoopyMain.width = 287 / 5.5;
    SnoopyMain.height = 385 / 5.5;
    SnoopyMain.rows = 1;
    SnoopyMain.cols = 3;
    SnoopyMain.currentFrame = 2;
    SnoopyMain.TimePerFrame = 90;
    SnoopyMain.pos.x = BOX * 10;
    SnoopyMain.pos.y = BOX * 5 - SnoopyMain.height;
    SnoopyMain.curentTimeLeft = SnoopyMain.TimePerFrame;
    SnoopyMain.surface = SDL_LoadBMP("../src/Snoppy/SnoopyMenu.bmp");

    // Bad Smoppy show in the menu
    BadSnoppyMain.frameWidth = 328;
    BadSnoppyMain.frameHeight = 427;
    BadSnoppyMain.width = 287 / 5;
    BadSnoppyMain.height = 385 / 5;
    BadSnoppyMain.rows = 1;
    BadSnoppyMain.cols = 3;
    BadSnoppyMain.currentFrame = 1;
    BadSnoppyMain.TimePerFrame = 85;
    BadSnoppyMain.pos.x = BOX * 12;
    BadSnoppyMain.pos.y = BOX * 5 - BadSnoppyMain.height;
    BadSnoppyMain.curentTimeLeft = BadSnoppyMain.TimePerFrame;
    BadSnoppyMain.surface = SDL_LoadBMP("../src/Snoppy/BadSnoppyMenu.bmp");

    // Check if loading player images was successful
    if (!playerUpSurface || !playerDownSurface || !playerLeftSurface || !playerRightSurface || !ActionSurface)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load player images: %s", SDL_GetError());
        EndGame();
        return;
    }

    // Create player textures
    playerUpTexture = SDL_CreateTextureFromSurface(render, playerUpSurface);
    playerDownTexture = SDL_CreateTextureFromSurface(render, playerDownSurface);
    playerLeftTexture = SDL_CreateTextureFromSurface(render, playerLeftSurface);
    playerRightTexture = SDL_CreateTextureFromSurface(render, playerRightSurface);
    ActionTexture = SDL_CreateTextureFromSurface(render, ActionSurface);
    SnoopyMain.texture = SDL_CreateTextureFromSurface(render, SnoopyMain.surface);
    BadSnoppyMain.texture = SDL_CreateTextureFromSurface(render, BadSnoppyMain.surface);

    // Check if creating player textures was successful
    if (!playerUpTexture || !playerDownTexture || !playerLeftTexture || !playerRightTexture || !ActionTexture)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to create player textures: %s", SDL_GetError());
        EndGame();
        return;
    }

    // Free player surfaces
    SDL_FreeSurface(playerUpSurface);
    SDL_FreeSurface(playerDownSurface);
    SDL_FreeSurface(playerLeftSurface);
    SDL_FreeSurface(playerRightSurface);
    SDL_FreeSurface(ActionSurface);
    SDL_FreeSurface(SnoopyMain.surface);
    SDL_FreeSurface(BadSnoppyMain.surface);
    // Initialize GameTimer
    GameTimer.w = WIDTH - 1;
    GameTimer.h = HIEGHT - 1;
    GameTimer.Totale = (GameTimer.w * 2 + GameTimer.h * 2) * 2 - 4;
    GameTimer.dec = 1;
    GameTimer.time = 0.3;
    totaleTime = GameTimer.time * 500;

    // Initialize blockMap
    blockMap.nbr = 5;
    blockMap.pos = (Position *)calloc(blockMap.nbr, sizeof(Position));
    if (blockMap.pos == NULL)
    {
        fprintf(stderr, "Memory allocation for blockMap failed.\n");
        exit(1); // or handle the error in an appropriate way
    }

    int blockPositions[][2] = {{2, 0}, {2, 1}, {2, 2}, {1, 2}, {0, 2}};
    for (int i = 0; i < blockMap.nbr; i++)
    {
        blockMap.pos[i].x = blockPositions[i][0];
        blockMap.pos[i].y = blockPositions[i][1];
    }

    // Initialize ball
    ball.pos.x = MAP_WIDTH / 2;
    ball.pos.y = MAP_HEIGHT / 2;
    ball.width = 25;
    ball.height = 25;
    ball.vel_x = 180;
    ball.vel_y = 140;

    // Set player position
    SetPlayerPositionTo(0, 0);

    // Example of Levels
    PlayerLevels.nbr = 6;
    PlayerLevels.list = (Level *)calloc(PlayerLevels.nbr, sizeof(Level));
    for (int i = 0; i < PlayerLevels.nbr; i++)
    {
        if (i < 3)
        {
            PlayerLevels.list[i].isOpen = true;
        }
        else
        {
            PlayerLevels.list[i].isOpen = false;
        }
        PlayerLevels.list[i].urlFile = (char *)calloc(50, sizeof(char));
    }
}

void drawBall()
{
    if (!Paused)
    {
        ballCollision();
    }
    SDL_Surface *ballSurface = SDL_LoadBMP("../src/ball.bmp");
    if (!ballSurface)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load BMP image for ball: %s", SDL_GetError());
        EndGame();
        return;
    }

    // Create texture from the ball surface
    SDL_Texture *ballTexture = SDL_CreateTextureFromSurface(render, ballSurface);
    SDL_FreeSurface(ballSurface);
    if (!ballTexture)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to create texture from surface for ball: %s", SDL_GetError());
        EndGame();
        return;
    }

    // Render ball texture
    SDL_Rect ballRect = {(int)ball.pos.x, (int)ball.pos.y, (int)ball.width, (int)ball.height};
    SDL_RenderCopy(render, ballTexture, NULL, &ballRect);
}

Position GetPlayerPosition()
{
    Position var;
    var.x = (int)(Snoppy.pos.x - 24) / BOX;
    var.y = (int)(Snoppy.pos.y - 24) / BOX;
    return var;
}

bool CheckCollision(Position a, Position b, float width, float height)
{
    return a.x * BOX < (b.x + width) * BOX &&
           (a.x + width) * BOX > b.x * BOX &&
           a.y * BOX < (b.y + height) * BOX &&
           (a.y + height) * BOX > b.y * BOX;
}

bool CheckBlockCollision(Position nextPosition)
{
    for (int i = 0; i < blockMap.nbr; i++)
    {
        if (CheckCollision(nextPosition, blockMap.pos[i], 1, 1))
        {
            return true; // Collision detected
        }
    }
    return false; // No collision
}

void SetPlayerPositionTo(int nextX, int nextY)
{
    if (nextX >= 0 && nextX < WIDTH - 1 && nextY >= 0 && nextY < HIEGHT - 1)
    {
        Position nextPosition = {nextX, nextY};

        if (!CheckBlockCollision(nextPosition))
        {
            Snoppy.pos.x = nextX * BOX + TIMER_WIDTH;
            Snoppy.pos.y = nextY * BOX + TIMER_WIDTH;
        }
        else
        {
            printf("Collision detected: Can't move to the position (%d, %d)\n", nextX, nextY);
        }
    }
    else
    {
        printf("Can't do a position out of the matrix");
    }
}

int IndexToRealPos(int index)
{
    return index * BOX + BOX / 2;
}

void ballCollision()
{
    float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0;
    last_frame_time = SDL_GetTicks();

    ball.pos.x += ball.vel_x * delta_time;
    ball.pos.y += ball.vel_y * delta_time;

    // Check collision with player
    Position playerPosition = GetPlayerPosition();
    if (ball.pos.x < playerPosition.x * BOX + BOX &&
        ball.pos.x + ball.width > playerPosition.x * BOX &&
        ball.pos.y < playerPosition.y * BOX + BOX &&
        ball.pos.y + ball.height > playerPosition.y * BOX)
    {
        printf("Ball collided with the player!\n");
        printf("Game Over: u died!\n");
        playing = false;
    }

    // Check collision with blocks
    for (int i = 0; i < blockMap.nbr; i++)
    {
        float boxRight = IndexToRealPos(blockMap.pos[i].x) + BOX;
        float boxBottom = IndexToRealPos(blockMap.pos[i].y) + BOX;

        if (ball.pos.x < boxRight && ball.pos.x + ball.width > IndexToRealPos(blockMap.pos[i].x) &&
            ball.pos.y < boxBottom && ball.pos.y + ball.height > IndexToRealPos(blockMap.pos[i].y))
        {
            float overlapX = fmin(fabs(ball.pos.x + ball.width - IndexToRealPos(blockMap.pos[i].x)),
                                  fabs(IndexToRealPos(blockMap.pos[i].x) + BOX - ball.pos.x));
            float overlapY = fmin(fabs(ball.pos.y + ball.height - IndexToRealPos(blockMap.pos[i].y)),
                                  fabs(IndexToRealPos(blockMap.pos[i].y) + BOX - ball.pos.y));
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

    // Check boundaries
    if (ball.pos.x < TIMER_WIDTH)
    {
        ball.pos.x = TIMER_WIDTH;
        ball.vel_x = -ball.vel_x;
    }
    if (ball.pos.x + ball.width > MAP_WIDTH + TIMER_WIDTH)
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

void HandelEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            EndGame();
        }
        if (PlayerInMenu)
        {
            switch (ObtionSousMenu)
            {
            case 0:
                Menu_1_Events(event);
                break;
            case 1:
                break;
            case 2:
                ListMenuEventsSelect(event);
                break;
            case 3:
                break;
            }
        }
        else
        {

            if (event.type == SDL_KEYDOWN && Paused == false && playing)
            {
                Snoppy.lastDirection = event.key.keysym.sym; // Set the lastDirection property

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
            PauseEvents(event);
        }
    }
}

void makeGrid()
{
    // Load grid image
    SDL_Surface *surface = SDL_LoadBMP("../src/grid.bmp");
    if (!surface)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load BMP image: %s", SDL_GetError());
        EndGame();
        return;
    }

    // Create texture from surface
    SDL_Texture *texture = SDL_CreateTextureFromSurface(render, surface);
    SDL_FreeSurface(surface);
    if (!texture)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to create texture from surface: %s", SDL_GetError());
        EndGame();
        return;
    }

    // Render grid texture
    SDL_Rect destinationRect = {TIMER_WIDTH, TIMER_WIDTH, BOX * (WIDTH - 1), BOX * (HIEGHT - 1)};
    SDL_RenderClear(render);
    SDL_RenderCopy(render, texture, NULL, &destinationRect);

    // Draw white rectangles
    SDL_SetRenderDrawColor(render, 255, 255, 255, 255); // White color
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            SDL_Rect topRect = {(i * (WIDTH * BOX - TIMER_WIDTH)), (j * (BOX * HIEGHT - TIMER_WIDTH)), TIMER_WIDTH, TIMER_WIDTH};
            SDL_RenderFillRect(render, &topRect);
        }
    }

    // Render timer, map, and player
    makeTimer();
    RenderMap();
    drawPlayer();
    if (Paused)
    {
        PauseGameRender();
    }
    SDL_RenderPresent(render);
}

void drawPlayer()
{
    SDL_Texture *playerTexture;

    // Determine which direction the player is moving
    if (Snoppy.lastDirection == SDLK_LEFT)
    {
        playerTexture = playerLeftTexture;
    }
    else if (Snoppy.lastDirection == SDLK_RIGHT)
    {
        playerTexture = playerRightTexture;
    }
    else if (Snoppy.lastDirection == SDLK_UP)
    {
        playerTexture = playerUpTexture;
    }
    else if (Snoppy.lastDirection == SDLK_DOWN)
    {
        playerTexture = playerDownTexture;
    }
    else
    {
        // Default to a specific direction (e.g., down) if no movement
        playerTexture = playerDownTexture;
    }

    // Render player texture
    SDL_Rect playerRect = {Snoppy.pos.x, Snoppy.pos.y, BOX, BOX};
    SDL_RenderCopy(render, playerTexture, NULL, &playerRect);

    // Print player position information
    printf("\nPlayer position: (x: %d, y: %d) | Real data: (x: %d, y: %d)", GetPlayerPosition().x, GetPlayerPosition().y, Snoppy.pos.x, Snoppy.pos.y);
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
        totaleLeft--;
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
        SDL_Rect topRect = {((i * (TIMER_WIDTH)) + TIMER_WIDTH) + (BOX / 12), (BOX * (HIEGHT - 1)) + (TIMER_WIDTH) + (BOX / 16), TIMER_WIDTH - BOX / 6, TIMER_WIDTH - BOX / 6};
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
        SDL_Rect topRect = {(BOX * (WIDTH - 1)) + (TIMER_WIDTH) + (BOX / 16), ((i * (TIMER_WIDTH)) + TIMER_WIDTH) - (TIMER_WIDTH) + (BOX / 12), TIMER_WIDTH - BOX / 6, TIMER_WIDTH - BOX / 6};
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
        SDL_Rect topRect = {((5 * BOX + (TIMER_WIDTH)) + (i * (TIMER_WIDTH)) + TIMER_WIDTH) + (BOX / 12), 0 + (BOX / 16), TIMER_WIDTH - BOX / 6, TIMER_WIDTH - BOX / 6};
        SDL_RenderFillRect(render, &topRect);
        totaleLeft--;
    }
}

void GameTimeClock()
{
    if (totaleTime < 0)
    {
        GameTimer.Totale -= GameTimer.dec;
        totaleTime = GameTimer.time * 1500;
    }
    else
    {
        totaleTime -= Frame;
    }
}

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

void drawCurserAction(Position pos)
{
    SDL_Rect ballRect = {pos.x, pos.y, BOX, BOX};
    SDL_RenderCopy(render, ActionTexture, NULL, &ballRect);
}

void RenderGame()
{
    SDL_RenderClear(render);
    SDL_SetRenderDrawColor(render, 0, 23, 27, 255);
    if (PlayerInMenu)
    {
        switch (ObtionSousMenu)
        {
        case 0:
            makeMenu();
            drawCurserAction(MenuPlayActionPointerPositions[ActionPointer]);
            drawSprite(&SnoopyMain);
            drawSprite(&BadSnoppyMain);
            break;
        case 1:
            break;
        case 2:
            RenderLevelsMenu();
            drawCurserAction(LevelMenuPlayActionPointerPositions[ActionPointer]);
            break;
        case 3:
            break;
        }
    }
    else
    {
        makeGrid();
        drawBall();
    }
    SDL_RenderPresent(render);
}

void Update()
{
    HandelEvents();
    if (PlayerInMenu)
    {
        MenuUpdate();
    }
    else
    {
        GamePlayUpdate();
    }
}

void PauseGameRender()
{
    // Load grid image
    SDL_Surface *surface = SDL_LoadBMP("../src/pauseBackground.bmp");
    if (!surface)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load BMP image: %s", SDL_GetError());
        EndGame();
        return;
    }

    // Create texture from surface
    SDL_Texture *texture = SDL_CreateTextureFromSurface(render, surface);
    SDL_FreeSurface(surface);
    if (!texture)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to create texture from surface: %s", SDL_GetError());
        EndGame();
        return;
    }

    // Render dark overlay
    SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(render, 0, 0, 0, 76); // 76 is approximately 30% opacity (76/255)
    SDL_RenderFillRect(render, NULL);

    // Set texture alpha modulation
    SDL_SetTextureAlphaMod(texture, 255); // Reset alpha modulation to full opacity

    // Render grid texture
    SDL_Rect destinationRect = {0, 0, BOX * WIDTH, BOX * HIEGHT};
    SDL_RenderCopy(render, texture, NULL, &destinationRect);

    // Present the renderer
    SDL_RenderPresent(render);
    if (Paused)
    {
        drawCurserAction(PauseActionPointerPositions[ActionPointer]);
    }
}

void PauseEvents(SDL_Event event)
{
    if (event.type == SDL_KEYDOWN)
    {
        if (event.key.keysym.sym == SDLK_ESCAPE)
        {
            Paused = true;
            int tmp_ball_posx = ball.pos.x;
            int tmp_ball_posy = ball.pos.y;
            ActionPointer = 0;
            while (Paused)
            {
                while (SDL_PollEvent(&event))
                {
                    if (event.type == SDL_KEYDOWN)
                    {
                        if (event.type == SDL_QUIT)
                        {
                            EndGame();
                        }
                        if (event.key.keysym.sym == SDLK_ESCAPE)
                        {
                            Paused = false;
                            last_frame_time = SDL_GetTicks();
                            ball.pos.x = tmp_ball_posx;
                            ball.pos.y = tmp_ball_posy;
                        }
                        else if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_DOWN)
                        {
                            if (ActionPointer == 0)
                            {
                                ActionPointer++;
                            }
                            else
                            {
                                ActionPointer--;
                            }
                        }
                        else if (event.key.keysym.sym == SDLK_RETURN)
                        {
                            Paused = false;
                            if (ActionPointer == 1)
                            {
                                EndGame();
                            }
                            else
                            {
                                last_frame_time = SDL_GetTicks();
                                ball.pos.x = tmp_ball_posx;
                                ball.pos.y = tmp_ball_posy;
                            }
                        }
                    }
                }
                SDL_RenderClear(render);
                SDL_SetRenderDrawColor(render, 0, 23, 27, 255);
                makeGrid();
                SDL_RenderPresent(render);
            }
        }
    }
}

void Menu_1_Events(SDL_Event event)
{
    if (event.type == SDL_KEYDOWN)
    {
        if (event.type == SDL_QUIT)
        {
            EndGame();
        }
        else if (event.key.keysym.sym == SDLK_UP)
        {
            ActionPointer--;
            if (ActionPointer < 0)
                ActionPointer = 2;
        }
        else if (event.key.keysym.sym == SDLK_DOWN)
        {
            ActionPointer++;
            if (ActionPointer > 2)
                ActionPointer = 0;
        }
        else if (event.key.keysym.sym == SDLK_RETURN)
        {
            switch (ActionPointer)
            {
            case 0:
                // Need to be chnaged to sleect first level
                PlayerInMenu = false;
                // ObtionSousMenu = 1;
                break;
            case 1:
                ObtionSousMenu = 2;
                break;
            case 2:
                ObtionSousMenu = 3;
                break;
            }
            ActionPointer = 0;
        }
    }
}

void ListMenuEventsSelect(SDL_Event event)
{
    if (event.type == SDL_KEYDOWN)
    {
        if (event.type == SDL_QUIT)
        {
            EndGame();
        }
        else if (event.key.keysym.sym == SDLK_UP)
        {
            ActionPointer--;
            if (ActionPointer < 0)
                ActionPointer = 6;
        }
        else if (event.key.keysym.sym == SDLK_DOWN)
        {
            ActionPointer++;
            if (ActionPointer > 6)
                ActionPointer = 0;
        }
        else if (event.key.keysym.sym == SDLK_RETURN)
        {
            switch (ActionPointer)
            {
            case 0:
                // Need to be chnaged to sleect first level
                // REutnn to the main menu
                ObtionSousMenu = 0;
                break;
            default:
                // here we will put a function that have the index and load the Game Setting like Map , Player Position ect Using
                // PlayerLevels Data and index in the ActionPointer
                break;
                ActionPointer = 0;
            }
        }
    }
}

void makeMenu()
{
    // Load grid image
    SDL_Surface *surface = SDL_LoadBMP("../src/menuHomeBG.bmp");
    if (!surface)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load BMP image: %s", SDL_GetError());
        EndGame();
        return;
    }

    // Create texture from surface
    SDL_Texture *texture = SDL_CreateTextureFromSurface(render, surface);
    SDL_FreeSurface(surface);
    if (!texture)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to create texture from surface: %s", SDL_GetError());
        EndGame();
        return;
    }

    // Render grid texture
    SDL_Rect destinationRect = {0, 0, BOX * (WIDTH), BOX * (HIEGHT)};
    SDL_RenderCopy(render, texture, NULL, &destinationRect);
}

void drawSprite(Sprite *sprite)
{
    SpriteUpdateAnimation(sprite);
    SDL_Rect srcRect = {(sprite->currentFrame % sprite->cols) * sprite->frameWidth,
                        (sprite->currentFrame / sprite->cols) * sprite->frameHeight,
                        sprite->frameWidth,
                        sprite->frameHeight};

    SDL_Rect destRect = {sprite->pos.x, sprite->pos.y, sprite->width, sprite->height};
    SDL_RenderCopy(render, sprite->texture, &srcRect, &destRect);
}

void SpriteUpdateAnimation(Sprite *sprite)
{
    if (sprite->curentTimeLeft <= 0)
    {
        sprite->curentTimeLeft = sprite->TimePerFrame;
        (sprite->currentFrame == sprite->cols - 1) ? sprite->currentFrame = 0 : sprite->currentFrame++;
    }
    sprite->curentTimeLeft -= Frame;
    if (sprite->pos.x <= (-sprite->width * 2))
    {
        sprite->pos.x = BOX * 10 + sprite->width;
    }
    sprite->pos.x -= 4;
}

void RenderLevelsMenu()
{
    SDL_Surface *surface;
    SDL_Texture *texture;

    surface = SDL_LoadBMP("../src/Snoppy/return.bmp");
    if (surface == NULL)
    {
        printf("Unable to load image ! SDL_Error: %s\n", SDL_GetError());
        return;
    }
    texture = SDL_CreateTextureFromSurface(render, surface);

    if (texture == NULL)
    {
        printf("Unable to create texture from ! SDL Error: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return;
    }

    SDL_FreeSurface(surface);

    int imgWidth = 531, imgHeight = 65;
    SDL_QueryTexture(texture, NULL, NULL, &imgWidth, &imgHeight);

    SDL_Rect renderRect = {(MAP_WIDTH / 2) - (MAP_WIDTH / 6), BOX, MAP_WIDTH / 2, BOX / 2};

    SDL_RenderCopy(render, texture, NULL, &renderRect);

    SDL_DestroyTexture(texture);

    for (int i = 0; i < PlayerLevels.nbr; ++i)
    {
        if (PlayerLevels.list[i].isOpen)
        {
            surface = SDL_LoadBMP("../src/Snoppy/Levels/level0.bmp");
        }
        else
        {
            surface = SDL_LoadBMP("../src/Snoppy/Levels/nothing.bmp");
        }
        if (surface == NULL)
        {
            printf("Unable to load image %s! SDL_Error: %s\n", (char *)PlayerLevels.list[i].urlFile, SDL_GetError());
            return;
        }
        texture = SDL_CreateTextureFromSurface(render, surface);

        if (texture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", (char *)PlayerLevels.list[i].urlFile, SDL_GetError());
            SDL_FreeSurface(surface);
            return;
        }

        SDL_FreeSurface(surface);

        int imgWidth = 531, imgHeight = 65;
        SDL_QueryTexture(texture, NULL, NULL, &imgWidth, &imgHeight);

        SDL_Rect renderRect = {(MAP_WIDTH / 2) - (MAP_WIDTH / 6), BOX * (i + 2), MAP_WIDTH / 2, BOX / 2};

        SDL_RenderCopy(render, texture, NULL, &renderRect);

        SDL_DestroyTexture(texture);
    }
}

void GamePlayUpdate()
{
    if (!Paused)
    {
        ballCollision();
        GameTimeClock();
        if (GameTimer.Totale <= 0)
        {
            printf("Game Over: Timer is up!\n");
            playing = false;
        }
    }
}

void MenuUpdate()
{
}
