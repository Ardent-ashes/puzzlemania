#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include"./header.hpp"



#define matrices_SIZE 4

SDL_Texture* background_texture = NULL;


typedef struct {
    int x, y;
} Position;
typedef struct {
    SDL_Texture* texture;
} glide;

glide glide_textures[matrices_SIZE * matrices_SIZE];
SDL_Texture* original_image_texture = NULL;

SDL_Texture* backgroundTextureslide = NULL;


SDL_Rect matrices_rect[matrices_SIZE][matrices_SIZE];
int matrices[matrices_SIZE][matrices_SIZE];
Position blank_pos;





SDL_Color text_color = {255, 255, 255}; 


void load_glide_images() {
    // Load images for each tile
    for (int i = 0; i < matrices_SIZE * matrices_SIZE; i++) {
        char filename[20];
        snprintf(filename, sizeof(filename), "images/img%d.jpg", i+1);
        SDL_Surface* surface = IMG_Load(filename);

        if (surface == NULL) {
            printf("Error loading image: %s\n", IMG_GetError());
            SDL_Quit();
            exit(1);
        }

        glide_textures[i].texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }

    // Load the original image
    char original_filename[200];
    snprintf(original_filename, sizeof(original_filename), "otherimages/original.jpg");
    SDL_Surface* original_surface = IMG_Load(original_filename);
    if (original_surface == NULL) {
        printf("Error loading original image: %s\n", IMG_GetError());
        SDL_Quit();
        exit(1);
    }

    original_image_texture = SDL_CreateTextureFromSurface(renderer, original_surface);
    SDL_FreeSurface(original_surface);

    // Load the background image
    char background_filename[200];
    snprintf(background_filename, sizeof(background_filename), "otherimages/dark.jpg");
    SDL_Surface* background_surface = IMG_Load(background_filename);
    if (background_surface == NULL) {
        printf("Error loading background image: %s\n", IMG_GetError());
        SDL_Quit();
        exit(1);
    }

    background_texture = SDL_CreateTextureFromSurface(renderer, background_surface);
    SDL_FreeSurface(background_surface);
}


void render_matrices() {
    SDL_RenderCopy(renderer, background_texture, NULL, NULL);
    int i, j;
    for (i = 0; i < matrices_SIZE; i++) {
        for (j = 0; j < matrices_SIZE; j++) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderFillRect(renderer, &matrices_rect[i][j]);

            if (matrices[i][j] != 0) {
                int glide_index = matrices[i][j] - 1;
                SDL_Rect dst = {matrices_rect[i][j].x, matrices_rect[i][j].y, 100, 100};
                SDL_RenderCopy(renderer, glide_textures[glide_index].texture, NULL, &dst);
            }
        }
    }

    // Render the original image on the right side
    SDL_Rect original_dst = {(matrices_SIZE * 100)+100, 100, 200, 200};
    SDL_RenderCopy(renderer, original_image_texture, NULL, &original_dst);
    
}

void swap_glide(Position* pos1, Position* pos2) {
    int temp = matrices[pos1->y][pos1->x];
    matrices[pos1->y][pos1->x] = matrices[pos2->y][pos2->x];
    matrices[pos2->y][pos2->x] = temp;

    blank_pos.x = pos1->x;
    blank_pos.y = pos1->y;
}

int is_valid_move(Position* pos) {
    return ((abs(pos->x - blank_pos.x) == 1 && pos->y == blank_pos.y) ||
            (abs(pos->y - blank_pos.y) == 1 && pos->x == blank_pos.x));
}





int count_inversions() {
    int inversions = 0;
    int i, j, k, l;

    for (i = 0; i < matrices_SIZE; i++) {
        for (j = 0; j < matrices_SIZE; j++) {
            for (k = i; k < matrices_SIZE; k++) {
                for (l = (k == i) ? j + 1 : 0; l < matrices_SIZE; l++) {
                    if (matrices[i][j] > matrices[k][l] && matrices[k][l] != 0) {
                        inversions++;
                    }
                }
            }
        }
    }

    return inversions;
}

int is_solvable() {
    int inversions = count_inversions();
    // Adjust for 0-based indexing and check the parity
    return ((matrices_SIZE % 2 == 1) && (inversions % 2 == 0)) || ((matrices_SIZE % 2 == 0) && ((blank_pos.y % 2 == 0) == (inversions % 2 == 1)));
}
int is_solved() {
    int i, j;
    for (i = 0; i < matrices_SIZE; i++) {
        for (j = 0; j < matrices_SIZE; j++) {
            if (matrices[i][j] != 0 && matrices[i][j] != i * matrices_SIZE + j + 1) {
                return 0;
            }
        }
    }
    return 1;
}



void shuffle_matrices() {
    int i, j;
    int flat_matrices[matrices_SIZE * matrices_SIZE];

    // Flatten the 2D matrices to a 1D array
    int index = 0;
    for (i = 0; i < matrices_SIZE; i++) {
        for (j = 0; j < matrices_SIZE; j++) {
            flat_matrices[index++] = matrices[i][j];
        }
    }

    // Shuffle the 1D array using Fisher-Yates algorithm
    for (i = matrices_SIZE * matrices_SIZE - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        // Swap
        int temp = flat_matrices[i];
        flat_matrices[i] = flat_matrices[j];
        flat_matrices[j] = temp;
    }

    // Unflatten the 1D array back to the 2D matrices
    index = 0;
    for (i = 0; i < matrices_SIZE; i++) {
        for (j = 0; j < matrices_SIZE; j++) {
            matrices[i][j] = flat_matrices[index++];
        }
    }

    // Find the position of the blank space
    for (i = 0; i < matrices_SIZE; i++) {
        for (j = 0; j < matrices_SIZE; j++) {
            if (matrices[i][j] == 0) {
                blank_pos.x = j;
                blank_pos.y = i;
                return;
            }
        }
    }
}

int slide()
{
    

    int i, j;
    for (i = 0; i < matrices_SIZE; i++) {
        for (j = 0; j < matrices_SIZE; j++) {
            matrices_rect[i][j] = (SDL_Rect){j * 100, i * 100, 100, 100};
        }
    }

    srand(time(NULL));
    int index = 0;
    for (i = 0; i < matrices_SIZE; i++) {
        for (j = 0; j < matrices_SIZE; j++) {
            matrices[i][j] = ++index;
        }
    }
    matrices[matrices_SIZE - 1][matrices_SIZE - 1] = 0;
    blank_pos.x = matrices_SIZE - 1;
    blank_pos.y = matrices_SIZE - 1;

    
    shuffle_matrices();
     if (!is_solvable()) {
        // Reshuffle until a solvable configuration is achieved
        while (!is_solvable()) {
            shuffle_matrices();
        }
    }
    load_glide_images();

    // Initial rendering
    render_matrices();
    SDL_RenderPresent(renderer);

    int quit = 0;
    SDL_Event e;
    SDL_Point clickPoint;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            } 
             if (e.type == SDL_MOUSEBUTTONDOWN) {
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            if(mouseX >=700 && mouseX <= 800 && mouseY >= 0 &&  mouseY<=50)
            {
                printf("tile quit yes\n");
                return -1;
             }

            }

            if (e.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                clickPoint.x = x;
                clickPoint.y = y;

                for (i = 0; i < matrices_SIZE; i++) {
                    for (j = 0; j < matrices_SIZE; j++) {
                        if (SDL_PointInRect(&clickPoint, &matrices_rect[i][j])) {
                            Position clicked_pos = {j, i};
                            if (is_valid_move(&clicked_pos)) {
                                swap_glide(&clicked_pos, &blank_pos);
                                render_matrices();
                                SDL_RenderPresent(renderer);

                                if (is_solved()) {
                                    printf("Congratulations! You have solved the puzzle!\n");
                                    quit = 1;
                                }
                            }
                        }
                    }
                }
            }
        }
       
        // Add a small delay to reduce CPU usage
        SDL_Delay(10);
    }

    // Add a delay before exiting to see the result
    SDL_Delay(2000);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    IMG_Quit();


    return 0;
}



