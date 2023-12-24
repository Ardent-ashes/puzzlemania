
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <SDL_mixer.h>
#include"./menu.cpp"
#include"./header.hpp"
#include"./start.cpp"
//#include"./tile.cpp"








int main(int argc, char* argv[]) {
    // if (!init()) {
    //     std::cerr << "Failed to initialize SDL." << std::endl;
    //     return -1;
    // }
    
     
  // matchinggame(); 
   init();
   registration();
   controll();
   //start();
   
   
    
    close();

    return 0;
}