#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
int append()
{
        FILE* filefinal = fopen("list.txt", "a");
    if (filefinal == NULL) {
        fprintf(stderr, "Error opening file for reading/writing\n");
        return 1;
    }


    FILE* ind = fopen("indscore.txt", "r");
    if (ind == NULL) {
        fprintf(stderr, "Error opening file for reading/writing\n");
        return 1;
    }

    // Read existing content
    char Content[100000] = "";
    fgets(Content, sizeof(Content), ind);

   
    
    fprintf(filefinal, "%s\n",Content);

    fclose(filefinal);


    return 0;
}
