
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include"./header.hpp"



#define TILE_SIZE 110
#define TILE_MARGIN 10
#define GRID_ROWS 4
#define GRID_COLS 4
#define TOTAL_TILES (GRID_ROWS * GRID_COLS)
#define TOTAL_COLORS (TOTAL_TILES / 2)
#define FORBIDDEN_TILE TILE_TEAL 
Mix_Chunk *tilinging;

typedef enum {
    TILE_EMPTY,
    TILE_RED,
    TILE_GREEN,
    TILE_BLUE,
    TILE_YELLOW,
    TILE_MAGENTA,
    TILE_CYAN,
    TILE_MAROON,
    TILE_TEAL,
} TileColor;

typedef struct {
    int x, y;
    TileColor color;
    bool flipped;
} Tile;


SDL_Texture* backgroundTexturetile = NULL;
SDL_Texture* unflippedTileTexture = NULL;
SDL_Texture* tileTextures[TOTAL_COLORS];

Tile grid[GRID_ROWS][GRID_COLS];
Tile* flippedTiles[2];
int numFlipped = 0;
bool quit = false;

// Function declarations
void initializeGrid();
void inittile() {
 
  

    backgroundTexturetile = IMG_LoadTexture(renderer, "otherimages/background.png");
    if (backgroundTexturetile == NULL) {
        printf("Failed to load background image! SDL_image Error: %s\n", IMG_GetError());
        exit(1);
    }

    unflippedTileTexture = IMG_LoadTexture(renderer, "tiles/cat.png");
    if (unflippedTileTexture == NULL) {
        printf("Failed to load unflipped tile image! SDL_image Error: %s\n", IMG_GetError());
        exit(1);
    }

    for (int i = 0; i < TOTAL_COLORS; i++) {
        char filename[50];
        sprintf(filename, "tiles/image%d.jpg", i + 1);
        tileTextures[i] = IMG_LoadTexture(renderer, filename);
        if (tileTextures[i] == NULL) {
            printf("Failed to load image %d! SDL_image Error: %s\n", i + 1, IMG_GetError());
            exit(1);
        }
    }

    srand(time(NULL));
    initializeGrid();
}

bool checkWin();
void drawGrid();
void drawTile(SDL_Rect rect, TileColor color);

void shuffleArray(TileColor array[], int size);
void savePlayerName(const char* playerName);
int countMismatches(int totalMatches, int *mismatchCount, Tile *flippedTiles[2]);
char* readPlayerName();


SDL_Event e;

int mismatchCount = 0;
// int matchedPairs = 0;
int totalMismatches = 0;
int forbiddenPairMatches = 0;
char tileplayer[] = {"tazkia"};

void initializeGrid() {
    TileColor colors[TOTAL_COLORS];
    for (int i = 0; i < TOTAL_COLORS; i++) {
        colors[i] = (TileColor)(i + 1);
    }

    shuffleArray(colors, TOTAL_COLORS);

    int colorCounts[TOTAL_COLORS];
    for (int i = 0; i < TOTAL_COLORS; i++) {
        colorCounts[i] = 0;
    }

    int totalTiles = GRID_ROWS * GRID_COLS;
    TileColor shuffledTiles[totalTiles];

    for (int i = 0; i < totalTiles; i++) {
        int randomColor;
        do {
            randomColor = rand() % TOTAL_COLORS;
        } while (colorCounts[randomColor] >= 2);

        colorCounts[randomColor]++;
        shuffledTiles[i] = colors[randomColor];
    }

    for (int i = 0; i < GRID_ROWS; i++) {
        for (int j = 0; j < GRID_COLS; j++) {
            grid[i][j].color = shuffledTiles[i * GRID_COLS + j];
            grid[i][j].flipped = false;
        }
    }
}


// Shuffle an array using the Fisher-Yates algorithm
void shuffleArray(TileColor array[], int size) {
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        // Swap array[i] and array[j]
        TileColor temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

bool checkWin() {
    int matchedPairs = 0;
    for (int i = 1; i <= TOTAL_COLORS; i++) {
        for (int j = 0; j < GRID_ROWS; j++) {
            for (int k = 0; k < GRID_COLS; k++) {
                if (grid[j][k].flipped && grid[j][k].color == i) {
                    if (i != FORBIDDEN_TILE) {
                        matchedPairs++;
                    }
                }
            }
        }
    }
    // If all non-forbidden pairs are matched, the player wins
    return (matchedPairs == 7);
}


int countMismatches(int totalMatches, int *mismatchCount, Tile *flippedTiles[2]) {
    if (flippedTiles[0]->color != flippedTiles[1]->color) {
        (*mismatchCount)++;
    }

    // Limit the mismatches to the total possible matches
    if (*mismatchCount > totalMatches) {
        *mismatchCount = totalMatches;
    }

    return *mismatchCount;
}
void drawTile(SDL_Rect rect, TileColor color) {
    SDL_RenderCopy(renderer, tileTextures[color - 1], NULL, &rect);
}
void drawGrid() {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, backgroundTexturetile, NULL, NULL);

    for (int i = 0; i < GRID_ROWS; i++) {
        for (int j = 0; j < GRID_COLS; j++) {
            SDL_Rect rect = {j * (TILE_SIZE + TILE_MARGIN), i * (TILE_SIZE + TILE_MARGIN), TILE_SIZE, TILE_SIZE};
            if (grid[i][j].flipped) {
                drawTile(rect, grid[i][j].color);
            } else {
                SDL_RenderCopy(renderer, unflippedTileTexture, NULL, &rect);
            }
        }
    }

    SDL_RenderPresent(renderer);
}
void handleEventtile(SDL_Event* e) {
    if (e->type == SDL_QUIT) {
        quit = true;
    } 
    else if (e->type == SDL_MOUSEBUTTONDOWN) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        int clickedRow = mouseY / (TILE_SIZE + TILE_MARGIN);
        int clickedCol = mouseX / (TILE_SIZE + TILE_MARGIN);
         if(mouseX >=700 && mouseX <= 800 && mouseY >= 0 &&  mouseY<=50)
        {
            printf("tile quit yes\n");
            back=1;
        }

        if (clickedRow >= 0 && clickedRow < GRID_ROWS && clickedCol >= 0 && clickedCol < GRID_COLS) {
            if (!grid[clickedRow][clickedCol].flipped && numFlipped < 2) {
                grid[clickedRow][clickedCol].flipped = true;
                flippedTiles[numFlipped] = &grid[clickedRow][clickedCol];
                numFlipped++;
            }
        }
    }
}


int starttile() {
    inittile();
    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            handleEventtile(&e);
        }

        drawGrid();

        if(back==1)
        {
            back=0;
            return -1;
        }

        if (numFlipped == 2)
        {

            int totalMatches = TOTAL_TILES / 2;
            int mismatches = countMismatches(totalMatches, &mismatchCount, flippedTiles); // Checking for number of mismatches
            SDL_Delay(500);

            // Inside the section where you check for a match after two tiles are flipped
            if (numFlipped == 2)
            {
                SDL_Delay(500);

                if (flippedTiles[0]->color == FORBIDDEN_TILE && flippedTiles[1]->color == FORBIDDEN_TILE)
                {
                    //printf("Oops %s! You matched the forbidden pair. Game over!\n", tileplayer);
                     Mix_FreeChunk(tilinging);
                    return 0;
                    //quit = true; // Closing the game when the forbidden pair is matched
                }
                else
                {
                    if (flippedTiles[0]->color == flippedTiles[1]->color)
                    {
                        int matchedPairs = 0;
                        for (int i = 1; i <= TOTAL_COLORS; i++)
                        {
                            if (i != FORBIDDEN_TILE)
                            {
                                int pairCount = 0;
                                for (int j = 0; j < GRID_ROWS; j++)
                                {
                                    for (int k = 0; k < GRID_COLS; k++)
                                    {
                                        if (grid[j][k].flipped && grid[j][k].color == i)
                                        {
                                            pairCount++;
                                        }
                                    }
                                }
                                if (pairCount == 2)
                                {
                                    matchedPairs++;
                                }
                            }
                        }

                        if (matchedPairs ==  7 && mismatches < 10)
                        {
                           // printf("Congratulations %s! You matched all pairs except the forbidden one. Proceed to Next Level!\n", tileplayer);
                            Mix_FreeChunk(tilinging);
                            return 1;
                            //quit = true; // Closing the game when 7 other pair is matched except for forbidden pair
                        }
                        if (/*matchedPairs == 7 &&*/ mismatches >= 10)
                        {
                           // printf("sorry %s! Too Many Mismatches. Try Again\n", player);
                            Mix_FreeChunk(tilinging);
                            return 0;
                            quit = true;
                        }
                    }
                    else
                    {
                        for (int i = 0; i < 2; i++)
                        {
                            flippedTiles[i]->flipped = false;
                        }
                    }
                    numFlipped = 0;
                }
            }
        }
    }
    return 2;
}