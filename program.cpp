#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int MENU_ITEM_HEIGHT = 50;
const int MENU_ITEM_WIDTH = 200;

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
SDL_Texture* gBackgroundTexture = nullptr;
TTF_Font* gFont = nullptr;
int showNewWindow = 0;

bool initializeSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    gWindow = SDL_CreateWindow("SDL Menu Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == nullptr) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == nullptr) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    if (TTF_Init() == -1) {
        printf("TTF_Init failed: %s\n", TTF_GetError());
        return false;
    }

    gFont = TTF_OpenFont("path_to_your_font_file.ttf", 24);
    if (gFont == nullptr) {
        printf("Failed to load font! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    return true;
}






bool loadBackgroundImage() {
    SDL_Surface* backgroundSurface = IMG_Load("background.jpg");
    if (backgroundSurface == nullptr) {
        printf("Failed to load background image! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    gBackgroundTexture = SDL_CreateTextureFromSurface(gRenderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);

    if (gBackgroundTexture == nullptr) {
        printf("Failed to create background texture! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

void closeSDL() {
    SDL_DestroyTexture(gBackgroundTexture);
    TTF_CloseFont(gFont);
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    TTF_Quit();
    SDL_Quit();
}

/*void drawMenu(SDL_Renderer* renderer, TTF_Font* font) {
    SDL_Color textColor = { 255, 255, 255 };
    SDL_Surface* textSurface1 = TTF_RenderText_Solid(font, "Menu Item 1", textColor);
    SDL_Texture* textTexture1 = SDL_CreateTextureFromSurface(renderer, textSurface1);
     SDL_Surface* textSurface2 = TTF_RenderText_Solid(font, "Menu Item 2", textColor);
    SDL_Texture* textTexture2 = SDL_CreateTextureFromSurface(renderer, textSurface2);

    SDL_Rect textRect1 = { (SCREEN_WIDTH - MENU_ITEM_WIDTH) / 2, (SCREEN_HEIGHT - MENU_ITEM_HEIGHT) / 2, MENU_ITEM_WIDTH, MENU_ITEM_HEIGHT };
    SDL_Rect textRect2 = { (SCREEN_WIDTH - MENU_ITEM_WIDTH-100) / 2, (SCREEN_HEIGHT - MENU_ITEM_HEIGHT-100) / 2, MENU_ITEM_WIDTH, MENU_ITEM_HEIGHT };
    SDL_RenderCopy(renderer, textTexture1, NULL, &textRect1);
    SDL_RenderCopy(renderer, textTexture2, NULL, &textRect2);

    SDL_FreeSurface(textSurface1);
    SDL_DestroyTexture(textTexture1);
    SDL_FreeSurface(textSurface2);
    SDL_DestroyTexture(textTexture2);
}*/

/*void drawNewWindow(SDL_Renderer* renderer, TTF_Font* font) {
    // Code to draw new window content
    // Similar to the previous example
    // ...

    // Here, we'll just draw a semi-transparent black rectangle to simulate a new window
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 128);
    SDL_Rect rect = { 100, 100, 400, 400 };
    SDL_RenderFillRect(renderer, &rect);
}*/
void handleoption()
{
        bool quit = false;
    SDL_Event e;

   while(!quit) {
        if(SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);

                // Check if the mouse click is within the menu item bounds
                if (x >= (SCREEN_WIDTH - MENU_ITEM_WIDTH) / 2 && x <= (SCREEN_WIDTH + MENU_ITEM_WIDTH) / 2 &&
                    y >= (SCREEN_HEIGHT - MENU_ITEM_HEIGHT) / 2 && y <= (SCREEN_HEIGHT + MENU_ITEM_HEIGHT) / 2) {
                    // Set the flag to show the new window
                    showNewWindow = 1;
                }
                  else if (x >= (SCREEN_WIDTH - MENU_ITEM_WIDTH-100) / 2 && x <= (SCREEN_WIDTH + MENU_ITEM_WIDTH+100) / 2 &&
                    y >= (SCREEN_HEIGHT - MENU_ITEM_HEIGHT-100) / 2 && y <= (SCREEN_HEIGHT + MENU_ITEM_HEIGHT+100) / 2) {
                    // Set the flag to show the new window
                    showNewWindow = 2;
                }
            }
       }

        SDL_RenderCopy(gRenderer, gBackgroundTexture, NULL, NULL);

        if(showNewWindow ==2)
        {

                SDL_Surface* backgroundSurface = IMG_Load("background.jpg");
                 if (backgroundSurface == nullptr) {
                 printf("Failed to load background image! SDL_Error: %s\n", SDL_GetError());
                
                 }

                 gBackgroundTexture = SDL_CreateTextureFromSurface(gRenderer, backgroundSurface);
                SDL_FreeSurface(backgroundSurface);

                 if (gBackgroundTexture == nullptr) {
                     printf("Failed to create background texture! SDL_Error: %s\n", SDL_GetError());
                     
                 }
                 SDL_Color textColor = { 255, 255, 255 };
    SDL_Surface* textSurface1 = TTF_RenderText_Solid(gFont, "Exit", textColor);
    SDL_Texture* textTexture1 = SDL_CreateTextureFromSurface(gRenderer, textSurface1);
     
    SDL_Rect textRect1 = { (SCREEN_WIDTH - MENU_ITEM_WIDTH-200) / 2, (SCREEN_HEIGHT - MENU_ITEM_HEIGHT) / 2, MENU_ITEM_WIDTH, MENU_ITEM_HEIGHT };
    
    SDL_RenderCopy(gRenderer, textTexture1, NULL, &textRect1);
   

    SDL_FreeSurface(textSurface1);
    SDL_DestroyTexture(textTexture1);
    int x, y;
                SDL_GetMouseState(&x, &y);

                // Check if the mouse click is within the menu item bounds
                if (x >= (SCREEN_WIDTH - MENU_ITEM_WIDTH-200) / 2 && x <= (SCREEN_WIDTH + MENU_ITEM_WIDTH) / 2 &&
                    y >= (SCREEN_HEIGHT - MENU_ITEM_HEIGHT) / 2 && y <= (SCREEN_HEIGHT + MENU_ITEM_HEIGHT) / 2) {
                    // Set the flag to show the new window
                    // handleoption();
                }
   
        }
        else if (showNewWindow==1) {
            drawNewWindow(gRenderer, gFont);
        }
        else {
            drawMenu(gRenderer, gFont);
        }

        SDL_RenderPresent(gRenderer);
    }

   

}

int main(int argc, char* args[]) {
    if (!initializeSDL()) {
        printf("Failed to initialize SDL!\n");
        return -1;
    }

    if (!loadBackgroundImage()) {
        printf("Failed to load background image!\n");
        closeSDL();
        return -1;
    }

    /*bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);

                // Check if the mouse click is within the menu item bounds
                if (x >= (SCREEN_WIDTH - MENU_ITEM_WIDTH) / 2 && x <= (SCREEN_WIDTH + MENU_ITEM_WIDTH) / 2 &&
                    y >= (SCREEN_HEIGHT - MENU_ITEM_HEIGHT) / 2 && y <= (SCREEN_HEIGHT + MENU_ITEM_HEIGHT) / 2) {
                    // Set the flag to show the new window
                    showNewWindow = 1;
                }
                  else if (x >= (SCREEN_WIDTH - MENU_ITEM_WIDTH-100) / 2 && x <= (SCREEN_WIDTH + MENU_ITEM_WIDTH+100) / 2 &&
                    y >= (SCREEN_HEIGHT - MENU_ITEM_HEIGHT-100) / 2 && y <= (SCREEN_HEIGHT + MENU_ITEM_HEIGHT+100) / 2) {
                    // Set the flag to show the new window
                    showNewWindow = 2;
                }
            }
        }

        SDL_RenderCopy(gRenderer, gBackgroundTexture, NULL, NULL);

        if(showNewWindow ==2)
        {

                SDL_Surface* backgroundSurface = IMG_Load("background.jpg");
                 if (backgroundSurface == nullptr) {
                 printf("Failed to load background image! SDL_Error: %s\n", SDL_GetError());
                
                 }

                 gBackgroundTexture = SDL_CreateTextureFromSurface(gRenderer, backgroundSurface);
                SDL_FreeSurface(backgroundSurface);

                 if (gBackgroundTexture == nullptr) {
                     printf("Failed to create background texture! SDL_Error: %s\n", SDL_GetError());
                     
                 }
        }
        else if (showNewWindow==1) {
            drawNewWindow(gRenderer, gFont);
        }
        else {
            drawMenu(gRenderer, gFont);
        }

        SDL_RenderPresent(gRenderer);
    }*/
    handleoption();

    closeSDL();
    return 0;
}
