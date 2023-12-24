#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

int main() {
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
    int x = 10;
    FILE* score = fopen("indscore.txt", "w");
    // if (score == NULL) {
    //     fprintf(stderr, "Error opening file: indscore.txt\n");
    //     return 1;
    // }
    fprintf(score, "%s %d\n", playername, x);

    // Close the score file
    fclose(score);

    return 0;
}
