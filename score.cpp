#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <SDL2/SDL_ttf.h>
#include"./header.hpp"

#define MAX_LINES 1000
#define MAX_LINE_LENGTH 256

SDL_Texture* backgroundTexturescore = NULL;

 bool renderBackgroundscore(SDL_Texture* backgroundTexturescore, SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, backgroundTexturescore, NULL, NULL);
    return true;
}


bool loadBackgroundImagescore() {
    
    SDL_Surface* backgroundSurface = IMG_Load("otherimages/score.jpg");
    if (backgroundSurface == nullptr) {
        printf("Failed to load background image! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    backgroundTexturescore = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);

    if (backgroundTexturescore == nullptr) {
        printf("Failed to create background texture! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    return true;
}

int scorelist()
{
    loadBackgroundImagescore();

    // Open the text file
    FILE* filelist = fopen("list.txt", "r");
    if (filelist == NULL) {
        fprintf(stderr, "Error opening file: list.txt\n");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Initialize the Liberation font
    const char* fontPath = "/usr/share/fonts/truetype/liberation2/LiberationSerif-Regular.ttf";  // Replace with the actual path to the Liberation font file
    TTF_Font* font = TTF_OpenFont(fontPath, 30);  // Replace 24 with the desired font size
    if (font == NULL) {
        fprintf(stderr, "Error loading font: %s\n", TTF_GetError());
        fclose(filelist);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Read lines and render text on the window
    char lines[MAX_LINES][MAX_LINE_LENGTH];
    int lineCount = 0;

    while (fgets(lines[lineCount], sizeof(lines[lineCount]), filelist) != NULL && lineCount <MAX_LINES) {
        
        lineCount++;
    }

    // Clear the window
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Event loop
    SDL_Event event;
    int quit = 0;

    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)) {
                quit = 1;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN) {
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            if(mouseX >=700 && mouseX <= 800 && mouseY >= 0 &&  mouseY<=50)
            {
                printf("tile quit yes\n");
                back=1;
                return -1;
             }

            }
        }
         SDL_RenderClear(renderer);
        renderBackgroundscore(backgroundTexturescore, renderer);
       
        

        
        // Render column headers
    SDL_Color textColor = {255, 255, 255, 255};  // white color
    SDL_Rect textRect = {10, 10, 0, 0};

    SDL_Surface* nameHeaderSurface = TTF_RenderText_Solid(font, "Name", textColor);
    SDL_Surface* scoreHeaderSurface = TTF_RenderText_Solid(font, "Score(out of 300)", textColor);

    SDL_Texture* nameHeaderText = SDL_CreateTextureFromSurface(renderer, nameHeaderSurface);
    SDL_Texture* scoreHeaderText = SDL_CreateTextureFromSurface(renderer, scoreHeaderSurface);

    SDL_FreeSurface(nameHeaderSurface);
    SDL_FreeSurface(scoreHeaderSurface);

    SDL_Rect nameHeaderRect = {10, 10, 0, 0};
    SDL_Rect scoreHeaderRect = {200, 10, 0, 0};  // Adjust the x-coordinate based on your layout

    SDL_QueryTexture(nameHeaderText, NULL, NULL, &nameHeaderRect.w, &nameHeaderRect.h);
    SDL_QueryTexture(scoreHeaderText, NULL, NULL, &scoreHeaderRect.w, &scoreHeaderRect.h);

    SDL_RenderCopy(renderer, nameHeaderText, NULL, &nameHeaderRect);
    SDL_RenderCopy(renderer, scoreHeaderText, NULL, &scoreHeaderRect);

    SDL_DestroyTexture(nameHeaderText);
    SDL_DestroyTexture(scoreHeaderText);


    FILE* individual = fopen("indscore.txt", "r");
    if (individual == NULL) {
        fprintf(stderr, "Error opening file for reading/writing\n");
        return 1;
    }
     char info[100000] = "";
    fgets(info, sizeof(info), individual);
     textRect.y = 40; 
    textRect.x = 10;  // Reset x-coordinate for the next line

    SDL_Surface* infoSurface = TTF_RenderText_Solid(font, info, textColor);
           

            SDL_Texture* infoTexture = SDL_CreateTextureFromSurface(renderer, infoSurface);

            SDL_FreeSurface(infoSurface);

            SDL_QueryTexture(infoTexture, NULL, NULL, &textRect.w, &textRect.h);
            SDL_RenderCopy(renderer, infoTexture, NULL, &textRect);
            SDL_DestroyTexture(infoTexture);

            textRect.x = 10;  // Reset x-coordinate for the next line
            textRect.y += textRect.h + 70;  // Adjust spacing between lines



    // Render lines on the window
    // Adjust the y-coordinate based on your layout

    for (int i = lineCount-1; i >=0; i--) {
        char name[MAX_LINE_LENGTH];
        char score[MAX_LINE_LENGTH];

        // Assuming the content in list.txt is formatted as "Name Score"
        if (sscanf(lines[i], "%s %s", name, score) == 2) {
            SDL_Surface* nameSurface = TTF_RenderText_Solid(font, name, textColor);
            SDL_Surface* scoreSurface = TTF_RenderText_Solid(font, score, textColor);

            SDL_Texture* nameTexture = SDL_CreateTextureFromSurface(renderer, nameSurface);
            SDL_Texture* scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);

            SDL_FreeSurface(nameSurface);
            SDL_FreeSurface(scoreSurface);

            SDL_QueryTexture(nameTexture, NULL, NULL, &textRect.w, &textRect.h);
            SDL_RenderCopy(renderer, nameTexture, NULL, &textRect);
            SDL_DestroyTexture(nameTexture);

            textRect.x = 200;  // Adjust the x-coordinate based on your layout

            SDL_QueryTexture(scoreTexture, NULL, NULL, &textRect.w, &textRect.h);
            SDL_RenderCopy(renderer, scoreTexture, NULL, &textRect);
            SDL_DestroyTexture(scoreTexture);

            textRect.x = 10;  // Reset x-coordinate for the next line
            textRect.y += textRect.h + 100;  // Adjust spacing between lines
        }
    }
    
    // Present the renderer
    SDL_RenderPresent(renderer);

        // SDL_RenderPresent(renderer);
    }
    renderBackgroundscore(backgroundTexturescore, renderer);

    // Close the file
    fclose(filelist);

    // Close the font
    TTF_CloseFont(font);
    SDL_DestroyTexture(backgroundTexturescore);

    // Cleanup and exit
    // SDL_DestroyRenderer(renderer);
    // SDL_DestroyWindow(window);
    // TTF_Quit();
    // SDL_Quit();
    return 0;

}

// int main()
// {
//     scorelist();
// }


