
#include"./menu.hpp"
#include"./collectcoin.cpp"
#include"./header.hpp"
#include"./tile.cpp"
#include"./append.cpp"
#include"./score.cpp"
#include"./slide.cpp"



const int Start_SIZE = 100;
const int END_SIZE = 50;
int page1=1;
int page2=0;
int inst=0;
int level3=0;
int prac=0;
int pracck;
int board=0;
int marks=0;
int sound=0;
Mix_Chunk *Effect;
Mix_Chunk *soundEffect;
struct Start {
    int x, y;
};

void pageone();
void pagetwo();
void handleEventspageone(bool&);
void handleEventspagetwo(bool&);
Start st;
Start end;


bool loadBackgroundImagewin() {
    SDL_Surface* backgroundSurface = IMG_Load("otherimages/win.jpg");
    if (backgroundSurface == nullptr) {
        printf("Failed to load background image! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);

    if (backgroundTexture == nullptr) {
        printf("Failed to create background texture! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    return true;
}
bool loadBackgroundImagelost() {
    SDL_Surface* backgroundSurface = IMG_Load("otherimages/lost.jpg");
    if (backgroundSurface == nullptr) {
        printf("Failed to load background image! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);

    if (backgroundTexture == nullptr) {
        printf("Failed to create background texture! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    return true;
}
bool loadBackgroundImageone() {
    SDL_Surface* backgroundSurface = IMG_Load("otherimages/b.jpg");
    if (backgroundSurface == nullptr) {
        printf("Failed to load background image! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);

    if (backgroundTexture == nullptr) {
        printf("Failed to create background texture one! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    return true;
}
bool loadImage() {
    SDL_Surface* backgroundSurface = IMG_Load("otherimages/q1.jpg");
    if (backgroundSurface == nullptr) {
        printf("Failed to load background image! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);

    if (backgroundTexture == nullptr) {
        printf("Failed to create background texture! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    return true;
}

bool loadBackgroundImageinstruction() {
    
    SDL_Surface* backgroundSurface = IMG_Load("otherimages/ins.jpg");
    if (backgroundSurface == nullptr) {
        printf("Failed to load background image! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);

    if (backgroundTexture == nullptr) {
        printf("Failed to create background texture! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    return true;
}

bool loadBackgroundImageprac() {
    
    SDL_Surface* backgroundSurface = IMG_Load("otherimages/practice.png");
    if (backgroundSurface == nullptr) {
        printf("Failed to load background image! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);

    if (backgroundTexture == nullptr) {
        printf("Failed to create background texture! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    return true;
}




void handleEventspageone(bool& quit) {
    //printf("dhuuuuu\n");
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            quit = true;
        }
        if (e.type == SDL_MOUSEBUTTONDOWN) {
                int prevBlockX = st.x;
                int prevBlockY = st.y;
                if(e.button.button==SDL_BUTTON_LEFT)
                {
                    int mouseX, mouseY;
                    SDL_GetMouseState(&mouseX, &mouseY);
                      if (mouseX >=200 && mouseX <= 200 + 200 && mouseY >= 80 &&  mouseY<= 80 + 60)
                      {
                        soundEffect = Mix_LoadWAV("sounds/click.wav");
                        if (soundEffect == nullptr) {
                        printf("no sound\n");
                        return;
                        }
                         Mix_PlayChannel(-1,soundEffect,0);
                        
                        //page1=0;
                        page2=1;
                        return;
                      }
                }
        }
        if (e.type == SDL_MOUSEBUTTONDOWN) {
               
                if(e.button.button==SDL_BUTTON_LEFT)
                {
                    int mouseX, mouseY;
                    SDL_GetMouseState(&mouseX, &mouseY);
                      if (mouseX >=30 && mouseX <= 30 + 200 && mouseY >= 170 &&  mouseY<= 170 + 60)
                      { 
                        //printf("practice on\n");
                        soundEffect = Mix_LoadWAV("sounds/click.wav");
                        if (soundEffect == nullptr) {
                        printf("no sound\n");
                        return;
                        }
                         Mix_PlayChannel(-1,soundEffect,0);
                                               
                        //page1=0;
                        //page2=1;
                        //inst=1;
                        prac=1;
                        return;
                      }
                }
        }

        if (e.type == SDL_MOUSEBUTTONDOWN) {
               
                if(e.button.button==SDL_BUTTON_LEFT)
                {
                    int mouseX, mouseY;
                    SDL_GetMouseState(&mouseX, &mouseY);
                      if (mouseX >=200 && mouseX <= 200 + 200 && mouseY >= 260 &&  mouseY<= 260 + 60)
                      {
                        soundEffect = Mix_LoadWAV("sounds/click.wav");
                        if (soundEffect == nullptr) {
                        printf("no sound\n");
                        return;
                        }
                         Mix_PlayChannel(-1,soundEffect,0);
                        
                        //page1=0;
                        //page2=1;
                        inst=1;
                        return;
                      }
                }
        }

        

        if (e.type == SDL_MOUSEBUTTONDOWN) {
               
                if(e.button.button==SDL_BUTTON_LEFT)
                {
                    int mouseX, mouseY;
                    SDL_GetMouseState(&mouseX, &mouseY);
                      if (mouseX >=30 && mouseX <= 30 + 200 && mouseY >= 350 &&  mouseY<= 350 + 60)
                      {
                        soundEffect = Mix_LoadWAV("sounds/click.wav");
                        if (soundEffect == nullptr) {
                        printf("no sound\n");
                        return;
                        }
                         Mix_PlayChannel(-1,soundEffect,0);
                        
                        //page1=0;
                        //page2=1;
                        board=1;
                        return;
                      }
                }
        }

        

        if (e.type == SDL_MOUSEBUTTONDOWN) {
                
                if(e.button.button==SDL_BUTTON_LEFT)
                {
                    int mouseX, mouseY;
                    SDL_GetMouseState(&mouseX, &mouseY);
                      if (mouseX >=200 && mouseX <= 200 + 200 && mouseY >= 200 &&  mouseY<= 440 + 60)
                      {
                        soundEffect = Mix_LoadWAV("sounds/click.wav");
                        if (soundEffect == nullptr) {
                        printf("no sound\n");
                        return;
                        }
                         Mix_PlayChannel(-1,soundEffect,0);
                        sound=0;
                        append();
                        marks=0;
                        Mix_FreeChunk(soundEffect);
                        Mix_FreeChunk(Effect);
                        exit(1);
                        close();
                        return;
                      }
                }
        }
    }
}

void handleEventspagetwo(bool& quit) {
    
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            quit = true;
        }
        if (e.type == SDL_MOUSEBUTTONDOWN) {
               
                if(e.button.button==SDL_BUTTON_LEFT)
                {
                    int mouseX, mouseY;
                    SDL_GetMouseState(&mouseX, &mouseY);
                      if (mouseX >=200 && mouseX <= 300 && mouseY >= 400 &&  mouseY<=450)
                      {
                        
                        
                        page2=0;
                        page1=0;
                        level3=1;
                        return;
                        
                      }
                }

            
        }
    }
}

void handleEventspagewin(bool& quit) {
    
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            quit = true;
        }
        if (e.type == SDL_MOUSEBUTTONDOWN) {
               
                if(e.button.button==SDL_BUTTON_LEFT)
                {
                    int mouseX, mouseY;
                    SDL_GetMouseState(&mouseX, &mouseY);
                      if (mouseX >=200 && mouseX <= 300 && mouseY >= 400 &&  mouseY<=450)
                      {
                        page2=0;
                        page1=1;
                        level3=0;
                        return;
                        
                      }
                }         

            
        }
    }
}

void handleEventspagelost(bool& quit) {
    
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            quit = true;
        }
        if (e.type == SDL_MOUSEBUTTONDOWN) {
               
                if(e.button.button==SDL_BUTTON_LEFT)
                {
                    int mouseX, mouseY;
                    SDL_GetMouseState(&mouseX, &mouseY);
                      if (mouseX >=200 && mouseX <= 300 && mouseY >= 400 &&  mouseY<=450)
                      {
                        page2=0;
                        page1=1;
                        level3=0;
                        return;
                        
                      }
                }         

            
        }
    }
}

void win()
{
    loadBackgroundImagewin();
    printf("i entered in win");

    
     bool quit = false;

    
    while (!quit) {
         handleEventspagewin(quit);
       

         SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

        if(page1==1)
        {
            return;
        }
        SDL_RenderPresent(renderer);
        }


}

void lost()
{
    loadBackgroundImagelost();

    
     bool quit = false;

    
    while (!quit) {
         handleEventspagelost(quit);
       

         SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

        if(page1==1)
        {
            return;
        }
        SDL_RenderPresent(renderer);
        }


}


void handleEventspageinstruction(bool& quit) {
    
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            quit = true;
        }
        if (e.type == SDL_MOUSEBUTTONDOWN) {
               
                if(e.button.button==SDL_BUTTON_LEFT)
                {
                    int mouseX, mouseY;
                    SDL_GetMouseState(&mouseX, &mouseY);
                      if (mouseX >=700 && mouseX <= 800 && mouseY >= 0 &&  mouseY<=50)
                      {

                        soundEffect = Mix_LoadWAV("sounds/click.wav");
                        if (soundEffect == nullptr) {
                        printf("no sound\n");
                        return;
                        }
                         Mix_PlayChannel(-1,soundEffect,0);
                        // page2=0;
                        // page1=1;
                        // level3=0;
                        inst=0;
                        return;
                        
                      }
                }         

            
        }
    }
}


void handleEventspageprac(bool& quit) {

    //printf("Dhuksii\n");
    
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            quit = true;
        }
        if (e.type == SDL_MOUSEBUTTONDOWN) {
               
                if(e.button.button==SDL_BUTTON_LEFT)
                {
                    int mouseX, mouseY;
                    SDL_GetMouseState(&mouseX, &mouseY);

                    if (mouseX >=80 && mouseX <= 80+100 && mouseY >= 300 &&  mouseY<=300+40)
                      {
                        soundEffect = Mix_LoadWAV("sounds/click.wav");
                        if (soundEffect == nullptr) {
                        printf("no sound\n");
                        return;
                        }
                         Mix_PlayChannel(-1,soundEffect,0);

                        pracck=1;
                        return;
                        
                      }

                   
                      
                }         

            
        }

        if (e.type == SDL_MOUSEBUTTONDOWN) {
               
                if(e.button.button==SDL_BUTTON_LEFT)
                {
                    int mouseX, mouseY;
                    SDL_GetMouseState(&mouseX, &mouseY);

                      if (mouseX >=350 && mouseX <= 350+100 && mouseY >= 500 &&  mouseY<=500+40)
                      {
                        Mix_Chunk *soundEffect = Mix_LoadWAV("sounds/click.wav");
                        if (soundEffect == nullptr) {
                        printf("no sound\n");
                        return;
                        }
                         Mix_PlayChannel(-1,soundEffect,0);
                        pracck=2;
                        return;
                        
                      }

                      
                }         

            
        }
        if (e.type == SDL_MOUSEBUTTONDOWN) {
               
                if(e.button.button==SDL_BUTTON_LEFT)
                {
                    int mouseX, mouseY;
                    SDL_GetMouseState(&mouseX, &mouseY);

                      if (mouseX >=600 && mouseX <= 600+100 && mouseY >= 300 &&  mouseY<=300+40)
                      {
                        soundEffect = Mix_LoadWAV("sounds/click.wav");
                        if (soundEffect == nullptr) {
                        printf("no sound\n");
                        return;
                        }
                         Mix_PlayChannel(-1,soundEffect,0);
                        pracck=3;
                        return;
                        
                      }

                      
                }         

            
        }


        if (e.type == SDL_MOUSEBUTTONDOWN) {
               
                if(e.button.button==SDL_BUTTON_LEFT)
                {
                    int mouseX, mouseY;
                    SDL_GetMouseState(&mouseX, &mouseY);

                      if (mouseX >=700 && mouseX <= 700+100 && mouseY >= 0 &&  mouseY<=50)
                      {
                        soundEffect = Mix_LoadWAV("sounds/click.wav");
                        if (soundEffect == nullptr) {
                        printf("no sound\n");
                        return;
                        }
                         Mix_PlayChannel(-1,soundEffect,0);
                        pracck=-1;
                        return;
                        
                      }

                      
                }         

            
        }
    }
}

int individual() {
    // Open the text file for reading
    FILE* fileind = fopen("player.txt", "r");
    if (fileind == NULL) {
        fprintf(stderr, "Error opening file: player.txt\n");
        return 1;
    }
    printf("hi\n");
    char playername[1000];
    if (fgets(playername, sizeof(playername), fileind) == NULL) {
        fprintf(stderr, "Error reading player name\n");
        fclose(fileind);
        return 1;
    }
    printf("Player name read: %s\n", playername); // Debug: Print the player name
    fclose(fileind);

    // Open the file for writing score
    
    FILE* score = fopen("indscore.txt", "w");
    // if (score == NULL) {
    //     fprintf(stderr, "Error opening file: indscore.txt\n");
    //     return 1;
    // }
    fprintf(score, "%s  %d\n", playername, marks);

    // Close the score file
    fclose(score);

    return 0;
}


void pageone()
{
    loadBackgroundImageone();
     
     bool quit = false;

     if(sound==0)
     {
            sound=1;
            Effect = Mix_LoadWAV("sounds/song.wav");
        if (Effect == nullptr) {
        printf("no sound\n");
        return;
            }
        Mix_PlayChannel(-1,Effect,0);
     }

     
    
    while (!quit) {
        handleEventspageone(quit);
        //printf("berrrr\n");

         SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

        if(page1==1 && page2!=1 && inst!=1 && prac!=1 && board!=1)
        {

        SDL_Rect startRect = { 200, 80, 200, 60 };
        SDL_SetRenderDrawColor(renderer, 0, 0, 153, 255); // Color of the player
        //SDL_RenderFillRect(renderer, &startRect);
         SDL_Rect exRect = { 30, 170, 200, 60 };
        SDL_SetRenderDrawColor(renderer, 0, 0, 153, 255); // Color of the player
        //SDL_RenderFillRect(renderer, &exRect);
        SDL_Rect startRect1 = { 200, 260, 200, 60 };
        SDL_SetRenderDrawColor(renderer, 0, 0, 153, 255); // Color of the player
        //SDL_RenderFillRect(renderer, &startRect1);
         SDL_Rect exRect1 = { 30, 350, 200, 60 };
        SDL_SetRenderDrawColor(renderer, 0, 0, 153, 255); // Color of the player
        //SDL_RenderFillRect(renderer, &exRect1);
        SDL_Rect startRect2 = { 200, 440, 200, 60 };
        SDL_SetRenderDrawColor(renderer, 0, 0, 153, 255); // Color of the player
        //SDL_RenderFillRect(renderer, &startRect2);


        SDL_Rect startRect3 = { 80, 300, 100, 40 };
        SDL_SetRenderDrawColor(renderer, 0, 0, 153, 255); // Color of the player
        //SDL_RenderFillRect(renderer, &startRect3);
        SDL_Rect startRect4 = { 600, 300, 100, 40 };
        SDL_SetRenderDrawColor(renderer, 0, 0, 153, 255); // Color of the player
        //SDL_RenderFillRect(renderer, &startRect4);
        SDL_Rect startRect5 = { 350, 500, 100, 40 };
        SDL_SetRenderDrawColor(renderer, 0, 0, 153, 255); // Color of the player
       //SDL_RenderFillRect(renderer, &startRect5);
         
        }  
        else
        {
            return;
        } 

        
        SDL_RenderPresent(renderer);
        }


}

void pagetwo()
{
    loadImage();
     

    
     bool quit = false;

    
    while (!quit) {
        handleEventspagetwo(quit);
       

         SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

        if(page2==1)
        {

         
        SDL_Rect rRect1 = { 200,400, 100, 50 };
        SDL_SetRenderDrawColor(renderer, 153,0, 0, 255); 
       // SDL_RenderFillRect(renderer, &rRect1);

        SDL_Rect rRect2 = { 500, 400, 100, 50 };
        SDL_SetRenderDrawColor(renderer, 153,0, 0, 255); 
        //SDL_RenderFillRect(renderer, &rRect2);
        }
        else
        {
            return;
        }
        SDL_RenderPresent(renderer);
        }


}


void instruction()
{
    //printf("inst on\n");
    loadBackgroundImageinstruction();

    
     bool quit = false;

    
    while (!quit) {
         handleEventspageinstruction(quit);
       

         SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

        if(inst==1)
        {
            //return;
        }
        else
        {
            return;
        }
        SDL_RenderPresent(renderer);
        }


}

void practice()
{
    //printf("inst on\n");
    loadBackgroundImageprac();

    
     bool quit = false;

    
    while (!quit) {
         handleEventspageprac(quit);
            //printf("behoisi\n");
            //printf("prack %d\n",pracck);
       

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);


        if(pracck==-1||pracck==3||pracck==2||pracck==1)
        {
            return;
        }
        SDL_RenderPresent(renderer);
        }


}



int ti=15;
int mr;
int gr;

void controll()
{
   
     bool quit = false;

    
    while (ti--) {
       

          printf("Hi\n");
          //game();
       

         SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
        pageone();
        if(page2==1)
        {


                printf("condition\n");    
               mr=starttile();
               
               if(mr==1)
               {
                    
                   marks=100;
                    pagetwo();
                    if(level3==1)
                    {
                        gr=game();
                        
                        if(gr==1)
                        {
                            page2=1;
                            pagetwo();
                            marks=200;
                            int sr=slide();
                            {
                                if(sr==1)
                                {
                                    marks=300;
                                     win();
                                    continue;
                                }
                                else if(sr==-1)
                                {
                                    lost();
                                    continue;
                                }
                            }
                           
                        }
                        else if(gr==0)
                        {
                            lost();
                            continue;
                        }
                        else if(gr==-1)
                        {
                            page2=0;
                            page1=0;
                            level3=1;
                            page2=0;
                            page1=1;
                            level3=0;
                            printf("Quit BLOCK\n");
                            continue;
                        }
                        // if(level3win==1)
                        // {
                        //     lost();
                        //     if(page1==1)
                        //     {
                        //         continue;
                        //     }
                        // }
                        
                        
                    }
                    
               }  
               else if(mr==0)
               {
                    
                        page2=0;
                        page1=0;
                        level3=1;
                    lost();
                    printf("LOST TILE\n");
                    
                    //mr=1;
                    continue;
               }
               else if(mr==-1)
               {

                        page2=0;
                        page1=0;
                        level3=1;
                        page2=0;
                        page1=1;
                        level3=0;
                        printf("Quit TILE\n");
                        continue;
               }

               
            
           
           
        }
        
        if(inst==1)
        {
            
            instruction();
            inst=0;
            page1=1;
            continue;
        }

        if(board==1)
        {
            individual();
            scorelist();
            board=0;
            page1=1;
            continue;
        }




        if(prac==1)
        {
            printf("practice on\n");
            while(pracck!=-1)
            {
                    practice();
            if(pracck==1)
            {
                int x=starttile();
                        page2=0;
                        page1=0;
                        level3=1;
                if(x==1)
                {
                    win();
                    prac=0;
                     pracck=0;
                     page1=1;
                    continue;
                }
                if(x==0)
                {
                    lost();
                    prac=0;
                     pracck=0;
                     page1=1;
                    continue;
                }
                if(x==-1)
                {
                    prac=0;
                     pracck=0;
                     page1=1;
                    continue;
                }
            }

            if(pracck==2)
            {
                int x=game();
                        page2=0;
                        page1=0;
                        level3=1;
                if(x==1)
                {
                    win();
                     prac=0;
                     pracck=0;
                     page1=1;
                    continue;
                }
                if(x==0)
                {
                    lost();
                    prac=0;
                    pracck=0;
                    page1=1;
                    continue;
                }
                if(x==-1)
                {
                    prac=0;     
                    pracck=0;
                    page1=1;
                    continue;
                        
                }
            }

            if(pracck==3)
            {
                int x=slide();
                        page2=0;
                        page1=0;
                        level3=1;
                if(x==1)
                {
                    win();
                    prac=0;
                     pracck=0;
                     page1=1;
                    continue;
                }
                if(x==-1)
                {
                    prac=0;
                     pracck=0;
                     page1=1;
                    continue;
                }
            }


            if(pracck==-1)
            {
                    prac=0;     
                    page1=1;
            }
            } 

            pracck=0;  
            

           
        }
        // if(page1==1)
        // {
           
        //     pageone();
        // }
      

}

}








