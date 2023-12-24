#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include"./header.hpp"




SDL_Texture* backgroundTexturestart = NULL;

 bool renderBackground(SDL_Texture* backgroundTexturestart, SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, backgroundTexturestart, NULL, NULL);
    return true;
}


bool loadBackgroundImagestart() {
    
    SDL_Surface* backgroundSurface = IMG_Load("otherimages/prac.jpg");
    if (backgroundSurface == nullptr) {
        printf("Failed to load background image! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    backgroundTexturestart = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);

    if (backgroundTexturestart == nullptr) {
        printf("Failed to create background texture! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    return true;
}


int registration()
{

    loadBackgroundImagestart();

    if (TTF_Init() != 0) {
        fprintf(stderr, "SDL_ttf initialization failed: %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    TTF_Font* font = TTF_OpenFont("font.ttf", 100);
    if (!font) {
        fprintf(stderr, "Font loading failed: %s\n", TTF_GetError());
        TTF_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    char playerName[50] = "";
    SDL_StartTextInput();

    SDL_Event event;
    int quit = 0;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = 1;
                    break;
                case SDL_TEXTINPUT:
                    strcat(playerName, event.text.text);
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_RETURN) {
                        quit = 1;
                    }
                    break;
            }
        }

       // SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        renderBackground(backgroundTexturestart, renderer);

        
        SDL_Color textColor = {255, 255, 255, 255};
        int maxTextWidth = 60;
        int textX = 100;
        int textY = 300;
        SDL_Surface* surface = TTF_RenderText_Solid(font, playerName, textColor);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_Rect textRect = {textX, textY, 200, 100};
        SDL_RenderCopy(renderer, texture, NULL, &textRect);

        SDL_RenderPresent(renderer);
    }

    SDL_StopTextInput();

    FILE* file = fopen("player.txt", "w");
    if (file == NULL) {
        fprintf(stderr, "Error opening file for reading/writing\n");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Read existing content
    char existingContent[100000] = "";
    fgets(existingContent, sizeof(existingContent), file);

    // Move the file pointer to the beginning
    fseek(file, 0, SEEK_SET);

    // Write new content followed by existing content
    fprintf(file, "%s", playerName);
    //fprintf(file, "%s", existingContent);

    fclose(file);

    // TTF_CloseFont(font);
    // SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(backgroundTexturestart);
    // SDL_DestroyWindow(window);
    // SDL_Quit();

    return 10;
}
