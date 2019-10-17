#include <vector>
#include <string>
#include <cstring>

#include "KingServent.h"

using namespace std;

People player;
RoomLocationFlags currentRoomFlags;
int seed = 0;
bool needPrintMap = false;

//Initilize starting Varibles
void init(){
    genCastle(); //Generate the Castle with a BSP system
    updateRoomFlags();  // Floodfill the room the player is in and see whats in it
    printString(genPlayerEnterRoomMessage()); // Print out a message describing room
}

//The main game loop
void gameLoop(){
    int currentCommand = 0;
    while (true){
        if (needPrintMap){
            printMap(castleMap);
        }
        updateRoomFlags();  // Floodfill the room the player is in and see whats in it
        do {
            currentCommand = getInput(); // Get a command
        } while(!isValidInput(currentCommand)); // Test is command can be exicuted
        executeCommand(currentCommand); // Execute the command
    }
}

int main(int argc, char *argv[]){
    for (int i = 0; i < argc; i++){
        if (strcmp(argv[i], "-s") == 0){
            if (argc > i){
                seed = atoi(argv[i + 1]);
            }
        }
        if (strcmp(argv[i], "-p") == 0){
            needPrintMap = true;
        }
    }
    init();
    gameLoop();
}