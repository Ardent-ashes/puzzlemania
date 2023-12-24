
#include"./collectcoin.hpp"
#include"./header.hpp"
 
const int COIN_SIZE = 20;
const int PLAYER_SIZE = 50;
const int ENEMY_SIZE = 30;
const int MAX_COINS = 5;
int remainingCoins = MAX_COINS;  
const float MOVE_DISTANCE = 5.0f;  // Distance to move on each key press
const float RANDOM_MOVE_INTERVAL = 5;
const float RANDOM_DIRECTION_CHANGE_INTERVAL = .005; 
int coincount=0;
int level3quit=0;
SDL_Texture* gBlockTexture = nullptr;
SDL_Texture* enemyTexture = nullptr;
SDL_Texture* coinTexture = nullptr;
Mix_Chunk *coining;
Mix_Chunk *collectend;



// SDL_Window* window = NULL;
// SDL_Renderer* renderer = NULL;
SDL_Texture* backgroundTexture = nullptr;
SDL_Texture* blockTexture = nullptr;
int v=112;

struct Coin {
    int x, y;
};

struct Player {
    int x, y;
};

struct Obstacle {
    int x, y, width, height;
};


std::vector<Obstacle>obstacles;
std::vector<Coin> coins;
Player player;
Player randomp;



bool loadBackgroundImage() {
    SDL_Surface* backgroundSurface = IMG_Load("otherimages/collector.png");
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



bool checkCollision(int x, int y) {
    for (const auto& obstacle : obstacles) {
        if (x < obstacle.x + obstacle.width &&
            x + PLAYER_SIZE > obstacle.x &&
            y < obstacle.y + obstacle.height &&
            y + PLAYER_SIZE > obstacle.y) {
            return true;  // Collision detected
        }
    }
    return false;  // No collision
}
bool checkcoin_obstacle_Collision(int x, int y) {
    for (const auto& obstacle : obstacles) {
        if (x < obstacle.x + obstacle.width &&
            x + COIN_SIZE > obstacle.x &&
            y < obstacle.y + obstacle.height &&
            y + COIN_SIZE > obstacle.y) {
            return true;  // Collision detected
        }
    }
    return false;  // No collision
}

// void spawnCoins() {
    
//     for (coincount=0; coincount < MAX_COINS; ) {
//         Coin coin;
        
//         coin.x = v % (SCREEN_WIDTH - COIN_SIZE);
//         coin.y = v% (SCREEN_HEIGHT - COIN_SIZE);
//             v=v*2;
//             if(checkcoin_obstacle_Collision(coin.x,coin.y))
//             {
//                 continue;
//             }
//             else
//             {
//                  coins.push_back(coin);
//                  coincount++;
//             }
//            }
// }


const int STEP_SIZE = 5;



void handleEvents(bool& quit) {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            quit = true;
        }


        if (e.type == SDL_MOUSEBUTTONDOWN) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        
         if(mouseX >=700 && mouseX <= 800 && mouseY >= 0 &&  mouseY<=50)
        {
            printf("tile quit yes\n");
            level3quit=1;
        }
        }

        if (e.type == SDL_KEYDOWN) {
                int prevBlockX = player.x;
                int prevBlockY = player.y;
            switch (e.key.keysym.sym) {
                
                case SDLK_UP:
                    if (player.y > 0) {
                        player.y -= STEP_SIZE;
                    }
                    break;
                case SDLK_DOWN:
                    if (player.y < SCREEN_HEIGHT - PLAYER_SIZE) {
                        player.y += STEP_SIZE;
                    }
                    break;
                case SDLK_LEFT:
                    if (player.x > 0) {
                        player.x -= STEP_SIZE;
                    }
                    break;
                case SDLK_RIGHT:
                    if (player.x < SCREEN_WIDTH - PLAYER_SIZE) {
                        player.x += STEP_SIZE;
                    }
                    break;
            }

            if (checkCollision(player.x, player.y)) {
                player.x = prevBlockX;
                 player.y = prevBlockY;
               // collisionOccurred = true;  // Set collision flag
            }
        }
    }
}

bool checkCoinCollision(const Coin& coin) {
    if (player.x < coin.x + COIN_SIZE &&
        player.x + PLAYER_SIZE > coin.x &&
        player.y < coin.y + COIN_SIZE &&
        player.y + PLAYER_SIZE > coin.y) {
        remainingCoins--;  
        return true;
    }
    return false;
}
void drawObstacles(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);  // Gray color for obstacles
    for (const auto& obstacle : obstacles) {
        SDL_Rect obstacleRect = { obstacle.x, obstacle.y, obstacle.width, obstacle.height };
        //SDL_RenderFillRect(renderer, &obstacleRect);
    }
}


bool loadBlockImage() {
    SDL_Surface* blockSurface = IMG_Load("otherimages/play.png");
    if (blockSurface == nullptr) {
        printf("Failed to load block image! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    gBlockTexture = SDL_CreateTextureFromSurface(renderer, blockSurface);
    SDL_FreeSurface(blockSurface);

    if (gBlockTexture == nullptr) {
        printf("Failed to create block texture! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

bool loadenemyImage() {
    SDL_Surface* blockSurface = IMG_Load("otherimages/enemy.png");
    if (blockSurface == nullptr) {
        printf("Failed to load block image! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    enemyTexture = SDL_CreateTextureFromSurface(renderer, blockSurface);
    SDL_FreeSurface(blockSurface);

    if (enemyTexture == nullptr) {
        printf("Failed to create block texture! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

bool loadcoinImage() {
    SDL_Surface* blockSurface = IMG_Load("otherimages/coin.png");
    if (blockSurface == nullptr) {
        printf("Failed to load block image! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    coinTexture = SDL_CreateTextureFromSurface(renderer, blockSurface);
    SDL_FreeSurface(blockSurface);

    if (coinTexture == nullptr) {
        printf("Failed to create block texture! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

void drawBlock(SDL_Renderer* renderer, int x, int y) {
    SDL_Rect blockRect = { x, y, PLAYER_SIZE, PLAYER_SIZE };
    SDL_RenderCopy(renderer, gBlockTexture, NULL, &blockRect);
}

void drawenemy(SDL_Renderer* renderer, int x, int y) {
    SDL_Rect enemyRect = { x, y, ENEMY_SIZE, ENEMY_SIZE };
    SDL_RenderCopy(renderer, enemyTexture, NULL, &enemyRect);
}

void drawcoin(SDL_Renderer* renderer, int x, int y) {
    SDL_Rect coinRect = { x, y, COIN_SIZE, COIN_SIZE };
    SDL_RenderCopy(renderer, coinTexture, NULL, &coinRect);
}





void moveRandomBlock(int& blockX, int& blockY, Uint32& lastMoveTime, Uint32& lastDirectionChangeTime) {
    static int randomDirection = rand() % 4;  // Initial random direction
    Uint32 currentTime = SDL_GetTicks();

    // Check if it's time to change direction
    if (currentTime - lastDirectionChangeTime >= RANDOM_DIRECTION_CHANGE_INTERVAL) {
        int newDirection = rand() % 4;

        // Change direction only if the new direction is not towards a structure
        switch (newDirection) {
        case 0:  // Move up
            if (blockY > 0 && !checkCollision(blockX, blockY - MOVE_DISTANCE)) {
                blockY -= static_cast<int>(MOVE_DISTANCE);
                randomDirection = newDirection;
            }
            break;
        case 1:  // Move down
            if (blockY < SCREEN_HEIGHT - PLAYER_SIZE && !checkCollision(blockX, blockY + MOVE_DISTANCE)) {
                blockY += static_cast<int>(MOVE_DISTANCE);
                randomDirection = newDirection;
            }
            break;
        case 2:  // Move left
            if (blockX > 0 && !checkCollision(blockX - MOVE_DISTANCE, blockY)) {
                blockX -= static_cast<int>(MOVE_DISTANCE);
                randomDirection = newDirection;
            }
            break;
        case 3:  // Move right
            if (blockX < SCREEN_WIDTH - PLAYER_SIZE && !checkCollision(blockX + MOVE_DISTANCE, blockY)) {
                blockX += static_cast<int>(MOVE_DISTANCE);
                randomDirection = newDirection;
            }
            break;
        }

        lastDirectionChangeTime = currentTime;
    }

    // Check if it's time to move the block
    if (currentTime - lastMoveTime >= RANDOM_MOVE_INTERVAL) {
        // Move in the current direction if not colliding with a structure
        switch (randomDirection) {
        case 0:  // Move up
            if (blockY > 0 && !checkCollision(blockX, blockY - MOVE_DISTANCE)) {
                blockY -= static_cast<int>(MOVE_DISTANCE);
            }
            break;
        case 1:  // Move down
            if (blockY < SCREEN_HEIGHT - PLAYER_SIZE && !checkCollision(blockX, blockY + MOVE_DISTANCE)) {
                blockY += static_cast<int>(MOVE_DISTANCE);
            }
            break;
        case 2:  // Move left
            if (blockX > 0 && !checkCollision(blockX - MOVE_DISTANCE, blockY)) {
                blockX -= static_cast<int>(MOVE_DISTANCE);
            }
            break;
        case 3:  // Move right
            if (blockX < SCREEN_WIDTH - PLAYER_SIZE && !checkCollision(blockX + MOVE_DISTANCE, blockY)) {
                blockX += static_cast<int>(MOVE_DISTANCE);
            }
            break;
        }

        lastMoveTime = currentTime;
    }
}

int game()
{
   // printf("remaining coin %d\n coincount %d\n ",remainingCoins,coincount);
     if(!loadBackgroundImage()||!loadBlockImage()||!loadenemyImage()||!loadcoinImage()) {
        printf("Failed to load images!\n");
     }
    randomp.x = 500; //(SCREEN_WIDTH - PLAYER_SIZE) / 4;  // Initial position for the random block
    randomp.y = 500; //(SCREEN_HEIGHT - PLAYER_SIZE) / 4;

    Uint32 lastRandomMoveTime = SDL_GetTicks();
    Uint32 lastRandomDirectionChangeTime = SDL_GetTicks();
    int randomDirection = rand() % 4;  // Initial random direction

     obstacles.push_back({ 0, 70, 150, 20 }); //horizontal
     obstacles.push_back({ 220, 70, 150, 20 });
     obstacles.push_back({590 , 70, 20, 200 }); //vertical
     obstacles.push_back({450 , 0, 20, 80 });
     obstacles.push_back({ 500, 160, 20, 200 });
     obstacles.push_back({ 65, 160, 350, 20 });
     obstacles.push_back({ 400, 250, 20, 65 });
     obstacles.push_back({ 300, 160, 20, 100 });
     obstacles.push_back({ 300, 245, 135, 20 });
     obstacles.push_back({ 80, 250, 20, 100 });
     obstacles.push_back({ 500, 250, 200, 20 });
     obstacles.push_back({ 50, 250, 180, 20 });
     obstacles.push_back({ 0, 420, 200, 20 });
     obstacles.push_back({ 200, 400, 20, 80 });
     obstacles.push_back({ 700, 0, 20, 50 });
     obstacles.push_back({ 700, 120, 20, 100 });
     obstacles.push_back({ 700, 320, 100, 20 });
     obstacles.push_back({ 100, 420, 20, 100 });
     obstacles.push_back({300 , 500, 20, 200 });
     obstacles.push_back({290 , 380, 100, 20 });
     obstacles.push_back({310 , 350, 20, 30 });
     obstacles.push_back({310 , 350, 20, 30 });
     obstacles.push_back({600 , 370, 20, 70 });
     obstacles.push_back({600 , 440, 70, 20 });
     obstacles.push_back({670 , 440, 20, 70 });
     obstacles.push_back({670 , 500, 50, 20 });
     obstacles.push_back({400 , 470, 100, 20 });
     obstacles.push_back({400 , 470, 20, 40 });
     obstacles.push_back({550 , 570, 20, 45 });
     obstacles.push_back({700 , 00, 100, 40 });

     Coin coin;
     coin.x=150;
     coin.y=20;
     coins.push_back(coin);
     coin.x=150;
     coin.y=200;
     coins.push_back(coin);
     coin.x=600;
     coin.y=30;
     coins.push_back(coin);
     coin.x=350;
     coin.y=100;
     coins.push_back(coin);
     coin.x=450;
     coin.y=400;
     coins.push_back(coin);
    //  coin.x=150;
    //  coin.y=20;
    //  coins.push_back(coin);
    //  coin.x=150;
    //  coin.y=20;
    //  coins.push_back(coin);
    //  coin.x=150;
    //  coin.y=20;
    //  coins.push_back(coin);
    //  coin.x=150;
    //  coin.y=20;
    //  coins.push_back(coin);
    //  coin.x=150;
    //  coin.y=20;
    //  coins.push_back(coin);


    
    //spawnCoins();
    bool quit = false;

    srand(time(NULL));

    while (!quit) {
        handleEvents(quit);
        //printf("remaining coin %d\n coincount %d\n ",remainingCoins,coincount);
      moveRandomBlock(randomp.x, randomp.y, lastRandomMoveTime, lastRandomDirectionChangeTime);
      if(level3quit==1)
        {
                
                        
            level3quit=0;
            remainingCoins=MAX_COINS;
             coins.clear();
             coincount=0;
             player.x=0;
             player.y=0;
             randomp.x = 500; 
             randomp.y = 500;
             Mix_FreeChunk(coining);
             Mix_FreeChunk(collectend);
            return -1;
        }
        if (randomp.x < player.x + PLAYER_SIZE &&
            randomp.x + ENEMY_SIZE > player.x &&
            randomp.y < player.y + PLAYER_SIZE &&
            randomp.y + ENEMY_SIZE > player.y) {
            printf("You lost\n");
            remainingCoins=MAX_COINS;
             coins.clear();
             coincount=0;
             player.x=0;
             player.y=0;
             randomp.x = 500; 
             randomp.y = 500;
             Mix_FreeChunk(coining);
            Mix_FreeChunk(collectend);
            //close();
            return 0 ;
        }
        
        SDL_RenderClear(renderer);
      SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
      drawObstacles(renderer);
         drawBlock(renderer, player.x, player.y);
         drawenemy(renderer, randomp.x, randomp.y);

       


       
        for (auto it = coins.begin(); it != coins.end();) {
            if (checkCoinCollision(*it)) {
                
                        
                it = coins.erase(it);
                coining = Mix_LoadWAV("sounds/coin.wav");
                        if (coining == nullptr) {
                        printf("no sound\n");
                        return 100;
                        }
                         Mix_PlayChannel(-1,coining,0);
            }
            else {
                // SDL_Rect coinRect = { it->x, it->y, COIN_SIZE, COIN_SIZE };
                // SDL_SetRenderDrawColor(renderer, 255, 223, 186, 255); // Color of the coins
                // SDL_RenderFillRect(renderer, &coinRect);
                drawcoin(renderer,it->x,it->y);

                it++;
            }
        }

       if (remainingCoins == 0) {
       printf("You win\n");
       remainingCoins=MAX_COINS;
       coins.clear();
       player.x=0;
       player.y=0;
       randomp.x = 500; 
       randomp.y = 500;
       coincount=0;
       level3win=1;
       Mix_FreeChunk(coining);
        Mix_FreeChunk(collectend);
       return 1;
        }
        //  SDL_Rect playerRect = { player.x, player.y, PLAYER_SIZE, PLAYER_SIZE };
        // SDL_SetRenderDrawColor(renderer, 0, 0, 153, 255); // Color of the player
        // SDL_RenderFillRect(renderer, &playerRect);
         
        // SDL_Rect rRect = { randomp.x, randomp.y, ENEMY_SIZE, ENEMY_SIZE };
        // SDL_SetRenderDrawColor(renderer, 153,0, 0, 255); 
        // SDL_RenderFillRect(renderer, &rRect);

       
        
        
        SDL_RenderPresent(renderer);
         }
         return 10;
}

