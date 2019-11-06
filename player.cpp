#include <string>

#include "KingServent.h"

using namespace std;

void movePlayer(int Y, int X){
    castleMap[player.Y][player.X].isCurrentPlayerLocation = false;
    player.Y = Y;
    player.X = X;
    castleMap[player.Y][player.X].isCurrentPlayerLocation = true;
}

bool canGetItemOfSize(int size){
    int amount = sizeOfItem[size];
    for (int i = 0; i < player.itemsInInventory.size(); i++){
        amount += sizeOfItem[player.itemsInInventory[i].size];
    }
    if (amount < MAX_INV_SIZE){
        return true;
    }
    return false;
}

/**
 * Input commands are all connected to a number:
 * 0: Reserved
 * 1:  "Look" - Used to examine surroundings  
 * 2:  "North" - Go north
 * 3:  "East" - Go east
 * 4:  "South" - Go south
 * 5:  "West" - Go west
 * 6:  "Quit" - Quit the game
 * 7:  "Yes"
 * 8:  "No"
 * 9:  "Examane" - describe on abj.
 * 10: "Inventory" - view inventory
 * 11: "Get" - Pick up an obj
 * 12: "Drop" - Drop an obj
**/
void executeCommand(int command){
    if (command == 1){
        if (gameFlags.input[1] == "None"){
            gameFlags.printCurrentRoomDescription = true;
        } else if (gameFlags.input[1] == "items" || gameFlags.input[1] == "i"){
            gameFlags.printCurrentRoomItems = true;
        } else if (gameFlags.input[1] == "furniture" || gameFlags.input[1] == "f"){
            gameFlags.printCurrentRoomFurniture = true;
        }
    } else if (1 < command && command < 6){
        for (int i = 0; i < currentRoomFlags.doors.size(); i++){
            if (currentRoomFlags.doors[i][2] == command - 1){
                switch (command){
                    case 2:
                        movePlayer(currentRoomFlags.doors[i][0] - 1, currentRoomFlags.doors[i][1]);
                        break;
                    case 3:
                        movePlayer(currentRoomFlags.doors[i][0], currentRoomFlags.doors[i][1] + 1);
                        break;
                    case 4:
                        movePlayer(currentRoomFlags.doors[i][0] + 1, currentRoomFlags.doors[i][1]);
                        break;
                    case 5:
                        movePlayer(currentRoomFlags.doors[i][0], currentRoomFlags.doors[i][1] - 1);
                        break;
                    default:
                        printString(miscResponses[2]);
                }
                gameFlags.printNewRoomMessage = true; // We moved into a new room
                break;
            }
        }
    } else if (command == 6){
        printString(miscResponses[4]);
        if (getInput() == 7){
            exit(0);
        }
        printString(miscResponses[5]);
    } else if (command == 9) {
        for (int i = 0; i < currentRoomFlags.itemsInRoom.size(); i++){
            if (gameFlags.input[1] == currentRoomFlags.itemsInRoom[i].name){
                printString(currentRoomFlags.itemsInRoom[i].description);
            }
        }
        for (int i = 0; i < currentRoomFlags.furnitureInRoom.size(); i++){
            if (gameFlags.input[1] == currentRoomFlags.furnitureInRoom[i].name){
                printString(currentRoomFlags.furnitureInRoom[i].description);
            }
        }
        for (int i = 0; i < player.itemsInInventory.size(); i++){
            if (gameFlags.input[1] == player.itemsInInventory[i].name){
                printString(player.itemsInInventory[i].description);
            }
        }
        for (int i = 0; i < player.elementaryItemsInInventory.size(); i++){
            if (gameFlags.input[1] == player.elementaryItemsInInventory[i].name){
                printString(player.elementaryItemsInInventory[i].description);
            }
        }
    } else if (command == 10){
        gameFlags.printInventory = true;
    } else if (command == 11) {
        int i;
        for (i = 0; i < currentRoomFlags.itemsInRoom.size(); i++){
            if (gameFlags.input[1] == currentRoomFlags.itemsInRoom[i].name){
                break;
            }
        }
        player.itemsInInventory.push_back(currentRoomFlags.itemsInRoom[i]);
        castleMap[currentRoomFlags.itemLocations[i].Y][currentRoomFlags.itemLocations[i].X].itemInTile = emptyItem;
        printString(miscResponses[11]);
    } else if (command == 12) {
        int i;
        for (i = 0; i < player.itemsInInventory.size(); i++){
            if (gameFlags.input[1] == player.itemsInInventory[i].name){
                break;
            }
        }
        bool giveTileItem = false;
        for (int y = currentRoomFlags.topLeftY; y < currentRoomFlags.width; y++){
            for (int x = currentRoomFlags.topLeftX; x < currentRoomFlags.hight; x++){
                if (castleMap[y][x].itemInTile.name == "Empty"){
                    castleMap[y][x].itemInTile = player.itemsInInventory[i];
                    giveTileItem = true;
                }
                break;
            }
            if (giveTileItem){
                break;
            }
        }
        player.itemsInInventory.erase(player.itemsInInventory.begin()+i);
        printString(miscResponses[12]);
    } else {
        printString(miscResponses[2]);
    }
}