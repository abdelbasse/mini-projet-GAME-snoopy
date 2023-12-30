#include <stdio.h>
#include "SDL.h"
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../cJSON/cJSON.h"

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
const int MOVEMENT_SPEED = 1;

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

typedef struct
{
    int levelIndex;
    Position snoopyPosition;
    Position ballPosition;
    Position *blockPositions;
    int blockCount;
    Position *birdPositions;
    int birdCount;
} LevelData;

// Astructure presenat the sprite for animation the snoppy in menu
typedef struct
{
    Position pos;
    int width, height, frameWidth, frameHeight, rows, cols;
    int currentFrame, startPosition;
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
    Position *pos;
    int nbr;
    int count;
} Berds;

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
Berds birdPositions;
int totaleTime;

SDL_Surface *playerUpSurface;
SDL_Surface *playerDownSurface;
SDL_Surface *playerLeftSurface;
SDL_Surface *playerRightSurface;
// Add ActionSurface (the cursore allow user for selection options)
SDL_Surface *ActionSurface;
SDL_Surface *Menusurface;
SDL_Surface *birdSurface;
SDL_Surface *ballSurface;
SDL_Texture *ballTexture;
// Declare player texture variables globally
SDL_Texture *playerUpTexture;
SDL_Texture *playerDownTexture;
SDL_Texture *playerLeftTexture;
SDL_Texture *playerRightTexture;
// Add ActionTexture (the cursore allow user for selection options)
SDL_Texture *ActionTexture;
SDL_Texture *Menutexture;

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
char *getStringUrlLevelByIndex(int);
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
void drawBird(Position);
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
LevelData *loadLevelDataFromFile(const char *);
cJSON *loadJSONFromFile(const char *);

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

LevelData *loadLevelDataFromFile(const char *filename)
{
    cJSON *root = loadJSONFromFile(filename);
    if (!root)
    {
        return NULL;
    }

    LevelData *levelData = (LevelData *)malloc(sizeof(LevelData));

    // Load level index
    levelData->levelIndex = cJSON_GetObjectItem(root, "levelIndex")->valueint;

    // Load player position
    cJSON *snoopyPosition = cJSON_GetObjectItem(root, "snoopyPosition");
    levelData->snoopyPosition.x = cJSON_GetObjectItem(snoopyPosition, "x")->valueint;
    levelData->snoopyPosition.y = cJSON_GetObjectItem(snoopyPosition, "y")->valueint;

    // Load ball position
    cJSON *ball = cJSON_GetObjectItem(root, "ball");
    levelData->ballPosition.x = cJSON_GetObjectItem(ball, "x")->valueint * BOX;
    levelData->ballPosition.y = cJSON_GetObjectItem(ball, "y")->valueint * BOX;

    // Load block positions
    cJSON *blockPositions = cJSON_GetObjectItem(root, "blockPositions");
    levelData->blockCount = cJSON_GetArraySize(blockPositions);
    levelData->blockPositions = malloc(levelData->blockCount * sizeof(Position));
    for (int i = 0; i < levelData->blockCount; i++)
    {
        cJSON *blockPosition = cJSON_GetArrayItem(blockPositions, i);
        levelData->blockPositions[i].x = cJSON_GetObjectItem(blockPosition, "x")->valueint;
        levelData->blockPositions[i].y = cJSON_GetObjectItem(blockPosition, "y")->valueint;
    }

    // Load bird positions
    cJSON *birdPositions = cJSON_GetObjectItem(root, "birdPositions");
    levelData->birdCount = cJSON_GetArraySize(birdPositions);
    levelData->birdPositions = malloc(levelData->birdCount * sizeof(Position));
    for (int i = 0; i < levelData->birdCount; i++)
    {
        cJSON *birdPosition = cJSON_GetArrayItem(birdPositions, i);
        levelData->birdPositions[i].x = cJSON_GetObjectItem(birdPosition, "x")->valueint;
        levelData->birdPositions[i].y = cJSON_GetObjectItem(birdPosition, "y")->valueint;
    }

    cJSON_Delete(root);

    return levelData;
}

cJSON *loadJSONFromFile(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("Error opening file");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *data = (char *)malloc(length + 1);
    fread(data, 1, length, file);
    fclose(file);

    data[length] = '\0';

    cJSON *root = cJSON_Parse(data);
    free(data);

    return root;
}

void initializeLevel(int levelIndex)
{
    char filename[50];
    sprintf(filename, "../src/Level%d.json", levelIndex);

    LevelData *levelData = loadLevelDataFromFile(filename);
    if (!levelData)
    {
        fprintf(stderr, "Failed to load level data from file.\n");
        exit(1);
    }

    blockMap.nbr = levelData->blockCount;
    blockMap.pos = (Position *)calloc(blockMap.nbr, sizeof(Position));
    if (blockMap.pos == NULL)
    {
        fprintf(stderr, "Memory allocation for blockMap failed.\n");
        exit(1);
    }
    for (int i = 0; i < blockMap.nbr; i++)
    {
        blockMap.pos[i].x = levelData->blockPositions[i].x;
        blockMap.pos[i].y = levelData->blockPositions[i].y;
    }

    // Initialize bird positions
    birdPositions.nbr = levelData->birdCount;
    birdPositions.count = birdPositions.nbr;
    birdPositions.pos = malloc(birdPositions.nbr * sizeof(Position));
    for (int i = 0; i < birdPositions.nbr; i++)
    {
        birdPositions.pos[i].x = levelData->birdPositions[i].x;
        birdPositions.pos[i].y = levelData->birdPositions[i].y;
    }

    ball.pos.x = levelData->ballPosition.x;
    ball.pos.y = levelData->ballPosition.y;
    // Initialize player position
    SetPlayerPositionTo(levelData->snoopyPosition.x, levelData->snoopyPosition.y);

    free(levelData);
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
    Menusurface = SDL_LoadBMP("../src/menuHomeBG.bmp");

    // Smoppy show in the menu
    SnoopyMain.frameWidth = 287;
    SnoopyMain.frameHeight = 385;
    SnoopyMain.width = 287 / 5.5;
    SnoopyMain.height = 385 / 5.5;
    SnoopyMain.rows = 1;
    SnoopyMain.cols = 3;
    SnoopyMain.currentFrame = 2;
    SnoopyMain.TimePerFrame = 140;
    SnoopyMain.pos.x = BOX * 10;
    SnoopyMain.startPosition = BOX * 10;
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
    BadSnoppyMain.TimePerFrame = 140;
    BadSnoppyMain.pos.x = BOX * 12;
    BadSnoppyMain.startPosition = BOX * 12;
    BadSnoppyMain.pos.y = BOX * 5 - BadSnoppyMain.height;
    BadSnoppyMain.curentTimeLeft = BadSnoppyMain.TimePerFrame;
    BadSnoppyMain.surface = SDL_LoadBMP("../src/Snoppy/BadSnoppyMenu.bmp");

    // Check if loading player images was successful
    if (!playerUpSurface || !playerDownSurface || !playerLeftSurface || !playerRightSurface || !ActionSurface || !Menusurface)
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
    Menutexture = SDL_CreateTextureFromSurface(render, Menusurface);
    // Check if creating player textures was successful
    if (!playerUpTexture || !playerDownTexture || !playerLeftTexture || !playerRightTexture || !ActionTexture || !Menutexture)
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
    SDL_FreeSurface(Menusurface);

    // Initialize GameTimer
    GameTimer.w = WIDTH - 1;
    GameTimer.h = HIEGHT - 1;
    GameTimer.Totale = (GameTimer.w * 2 + GameTimer.h * 2) * 2 - 4;
    GameTimer.dec = 1;
    GameTimer.time = 0.3;
    totaleTime = GameTimer.time * 500;

    // Initialize blockMap

    // Initialize ball

    ball.width = 25;
    ball.height = 25;
    ball.vel_x = 200;
    ball.vel_y = 200;
    initializeLevel(1);
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
    if (ballTexture == NULL)
    {
        SDL_Surface *ballSurface = SDL_LoadBMP("../src/ball.bmp");
        if (!ballSurface)
        {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load BMP image for ball: %s", SDL_GetError());
            EndGame();
            return;
        }

        // Create texture from the ball surface
        ballTexture = SDL_CreateTextureFromSurface(render, ballSurface);
        SDL_FreeSurface(ballSurface);
        if (!ballTexture)
        {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to create texture from surface for ball: %s", SDL_GetError());
            EndGame();
            return;
        }
    }

    // Render ball texture
    SDL_Rect ballRect = {(int)ball.pos.x, (int)ball.pos.y, (int)ball.width, (int)ball.height};
    SDL_RenderCopy(render, ballTexture, NULL, &ballRect);
}

void drawBird(Position birdPosition)
{
    SDL_Surface *birdSurface = SDL_LoadBMP("../src/bird.bmp");

    if (!birdSurface)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load BMP image for bird: %s", SDL_GetError());
        EndGame();
        return;
    }
    SDL_Rect destRect = {(birdPosition.x * BOX) + TIMER_WIDTH, (birdPosition.y * BOX) + TIMER_WIDTH, BOX, BOX};

    SDL_Texture *birdTexture = SDL_CreateTextureFromSurface(render, birdSurface);
    SDL_FreeSurface(birdSurface);
    SDL_RenderCopy(render, birdTexture, NULL, &destRect);

    SDL_DestroyTexture(birdTexture);
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
            return true;
        }
    }
    return false;
}

bool CheckBirdCollision(Position nextPosition)
{
    for (int i = 0; i < birdPositions.nbr; i++)
    {
        if (CheckCollision(nextPosition, birdPositions.pos[i], 1, 1))
        {
            return true;
        }
    }
    return false;
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

void birdCollision()
{
    Position playerPosition = GetPlayerPosition();

    for (int i = 0; i < birdPositions.nbr; i++)
    {
        if (CheckCollision(playerPosition, birdPositions.pos[i], 1, 1))
        {
            birdPositions.pos[i].x = -2;
            birdPositions.pos[i].y = -2;
            birdPositions.count--;
        }
    }
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
            float overlapX = fmin(abs(ball.pos.x + ball.width - IndexToRealPos(blockMap.pos[i].x)),
                                  abs(IndexToRealPos(blockMap.pos[i].x) + BOX - ball.pos.x));
            float overlapY = fmin(abs(ball.pos.y + ball.height - IndexToRealPos(blockMap.pos[i].y)),
                                  abs(IndexToRealPos(blockMap.pos[i].y) + BOX - ball.pos.y));
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
// Define a constant for movement speed

void HandelEvents()
{
    SDL_Event event;
    static Uint32 lastMoveTime = 0;

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
                if (event.key.keysym.sym == SDLK_LEFT ||
                    event.key.keysym.sym == SDLK_RIGHT ||
                    event.key.keysym.sym == SDLK_UP ||
                    event.key.keysym.sym == SDLK_DOWN)
                {
                    Uint32 currentTime = SDL_GetTicks();
                    if (currentTime - lastMoveTime >= 100) // Adjust the delay as needed
                    {
                        Snoppy.lastDirection = event.key.keysym.sym;

                        if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_RIGHT)
                        {
                            SetPlayerPositionTo(GetPlayerPosition().x + (event.key.keysym.sym == SDLK_LEFT ? -MOVEMENT_SPEED : MOVEMENT_SPEED), GetPlayerPosition().y);
                        }

                        if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_DOWN)
                        {
                            SetPlayerPositionTo(GetPlayerPosition().x, GetPlayerPosition().y + (event.key.keysym.sym == SDLK_UP ? -MOVEMENT_SPEED : MOVEMENT_SPEED));
                        }

                        lastMoveTime = currentTime;
                    }
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
    if (!PlayerInMenu)
    {
        RenderMap();
        drawPlayer();
        drawBall();
    }
    for (int i = 0; i < birdPositions.nbr; i++)
    {
        printf("hello %d", i);
        drawBird(birdPositions.pos[i]);
    }
    if (Paused)
    {
        PauseGameRender();
    }
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
            if (!PlayerLevels.list[ActionPointer - 1].isOpen)
            {
                ObtionSousMenu = 0;
            }
            else
            {
                switch (ActionPointer)
                {
                case 0:
                    ObtionSousMenu = 0;
                    break;
                default:
                    PlayerInMenu = false;
                    initializeLevel(ActionPointer);
                    ObtionSousMenu = 0;
                    break;
                }
            }
            ActionPointer = 0;
        }
    }
}

void makeMenu()
{
    SDL_Rect destinationRect = {0, 0, BOX * (WIDTH), BOX * (HIEGHT)};
    SDL_RenderCopy(render, Menutexture, NULL, &destinationRect);
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
    if (sprite->pos.x <= (sprite->startPosition - MAP_WIDTH * 2))
    {
        sprite->pos.x = sprite->startPosition;
    }
    sprite->pos.x -= 3;
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
            surface = SDL_LoadBMP(getStringUrlLevelByIndex(i));
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
        birdCollision();
        GameTimeClock();
        if (birdPositions.count == 0)
        {
            // incriment the level clear the screen and reset everything
        }
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

char *getStringUrlLevelByIndex(int index)
{
    switch (index)
    {
    case 0:
        return "../src/Snoppy/Levels/level0.bmp";
        break;
    case 1:
        return "../src/Snoppy/Levels/level1.bmp";
        break;
    case 2:
        return "../src/Snoppy/Levels/level2.bmp";
        break;
    case 3:
        return "../src/Snoppy/Levels/level3.bmp";
        break;
    case 4:
        return "../src/Snoppy/Levels/level4.bmp";
        break;
    case 5:
        return "../src/Snoppy/Levels/level6.bmp";
        break;
    default:
        break;
    }
}
