#include <vector>
#include <string>
#include <cstring>

#include "KingServent.h"

using namespace std;

People player;
RoomLocationFlags currentRoomFlags;
GameFlags gameFlags;
int seed = 0;
bool needPrintMap = false;

Furniture emptyFurniture = {"Empty"};
Item emptyItem = {"Empty"};
People emptyPerson = {"Empty"};

//Initilize starting Varibles
void init(){

    player.itemsInInventory.push_back(items[15]);
    player.itemsInInventory.push_back(items[14]);

    genCastle(); //Generate the Castle with a BSP system
    updateRoomFlags();  // Floodfill the room the player is in and see whats in it
    gameFlags.printNewRoomMessage = true; // Tell printMessages() we're in a new room
    printMessages(); // What's in our first room
}

//The main game loop
void gameLoop(){
    int currentCommand = 0;
    while (true){
        if (needPrintMap){
            printMap();
        }
        do {
            currentCommand = getInput(); // Get a command
        } while(!isValidInput(currentCommand)); // Test is command can be executed
        executeCommand(currentCommand); // Execute the command
        updateRoomFlags();  // Floodfill the room the player is in and see whats in it
        printMessages(); // The player did something, tell them what happend
    }
}

int main(int argc, char *argv[]){
    for (int i = 0; i < argc; i++){
        if (strcmp(argv[i], "-s") == 0){ // set seed
            if (argc > i){
                seed = atoi(argv[i + 1]);
            }
        }
        if (strcmp(argv[i], "-p") == 0){ // print out map every turn
            needPrintMap = true;
        }
    }
    init();
    gameLoop();
}