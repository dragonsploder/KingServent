#include <vector>
#include <string>

#include "KingServent.h"

using namespace std;

Player player;
RoomLocationFlags currentRoomFlags;

//Initilize starting Varibles
void init(){
    //Generate the Castle with a BSP system
    genCastle();
}

//The main game loop
void gameLoop(){
    //Floodfill the room the player is in and see whats in it
    updateRoomFlags();
    //Print out a message describing room
    printString(genPlayerEnterRoomMessage());
}

int main(){
    getInput();
    init();
    gameLoop();
}