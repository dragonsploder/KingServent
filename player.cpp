#include <string>

#include "KingServent.h"

using namespace std;

void movePlayer(int Y, int X){ // move the player to new location
    castleMap[player.Y][player.X].isCurrentPlayerLocation = false; // change old tile
    player.Y = Y; // update player
    player.X = X; // update player
    castleMap[player.Y][player.X].isCurrentPlayerLocation = true; // change new tile
}

bool canGetItemOfSize(int size){ // Can the player pick up an item with int size
    int amount = sizeOfItem[size]; // Get the actual weight of the item
    for (int i = 0; i < player.itemsInInventory.size(); i++){ // for every other item in player inventory
        amount += sizeOfItem[player.itemsInInventory[i].size]; // add the weight to the total
    }
    if (amount < MAX_INV_SIZE){ // if the total size is less then the max carrying capacity
        return true; // the player can pick it up
    }
    return false; // the player can't
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
    if (command == 1){ // look
        if (gameFlags.input[1] == "None"){ // generic look
            gameFlags.printCurrentRoomDescription = true;
        } else if (gameFlags.input[1] == "items" || gameFlags.input[1] == "i"){ // look specificily at items
            gameFlags.printCurrentRoomItems = true; 
        } else if (gameFlags.input[1] == "furniture" || gameFlags.input[1] == "f"){ // look specificily at furniture
            gameFlags.printCurrentRoomFurniture = true;
        }
    } else if (1 < command && command < 6){ // move command
        for (int i = 0; i < currentRoomFlags.doors.size(); i++){ // for every possible exit
            if (currentRoomFlags.doors[i][2] == command - 1){ // if this is the exit the player want's
                switch (command){
                    case 2: // move north
                        movePlayer(currentRoomFlags.doors[i][0] - 1, currentRoomFlags.doors[i][1]);
                        break;
                    case 3: // move east
                        movePlayer(currentRoomFlags.doors[i][0], currentRoomFlags.doors[i][1] + 1);
                        break;
                    case 4: // move sout
                        movePlayer(currentRoomFlags.doors[i][0] + 1, currentRoomFlags.doors[i][1]);
                        break;
                    case 5: // move west
                        movePlayer(currentRoomFlags.doors[i][0], currentRoomFlags.doors[i][1] - 1);
                        break;
                    default:
                        printString(miscResponses[2]); // we messed somthing up
                }
                gameFlags.printNewRoomMessage = true; // We moved into a new room so tell the player
                break;
            }
        }
    } else if (command == 6){ // quit game
        printString(miscResponses[4]);
        if (getInput() == 7){ // make sure
            exit(0);
        }
        printString(miscResponses[5]); // "Ok"
    } else if (command == 9) { // examine
        for (int i = 0; i < currentRoomFlags.itemsInRoom.size(); i++){ // find the item that they want to examine
            if (gameFlags.input[1] == currentRoomFlags.itemsInRoom[i].name){
                printString(currentRoomFlags.itemsInRoom[i].description);
            }
        }
        for (int i = 0; i < currentRoomFlags.furnitureInRoom.size(); i++){ // find the furniture that they want to examine
            if (gameFlags.input[1] == currentRoomFlags.furnitureInRoom[i].name){
                printString(currentRoomFlags.furnitureInRoom[i].description);
            }
        }
        for (int i = 0; i < player.itemsInInventory.size(); i++){ // find the item that they want to examine
            if (gameFlags.input[1] == player.itemsInInventory[i].name){
                printString(player.itemsInInventory[i].description);
            }
        }
        for (int i = 0; i < player.elementaryItemsInInventory.size(); i++){ // find the elementray item that they want to examine
            if (gameFlags.input[1] == player.elementaryItemsInInventory[i].name){
                printString(player.elementaryItemsInInventory[i].description);
            }
        }
    } else if (command == 10){ // print inventory
        gameFlags.printInventory = true;
    } else if (command == 11) { // get an item
        int i;
        for (i = 0; i < currentRoomFlags.itemsInRoom.size(); i++){ //find the item
            if (gameFlags.input[1] == currentRoomFlags.itemsInRoom[i].name){
                break;
            }
        }
        player.itemsInInventory.push_back(currentRoomFlags.itemsInRoom[i]); // add it to player inventory
        castleMap[currentRoomFlags.itemLocations[i].Y][currentRoomFlags.itemLocations[i].X].itemInTile = emptyItem; // remove it from the ground
        printString(miscResponses[11]);
    } else if (command == 12) { // drop an item
        int i;
        for (i = 0; i < player.itemsInInventory.size(); i++){ // find the itms
            if (gameFlags.input[1] == player.itemsInInventory[i].name){
                break;
            }
        }
        bool giveTileItem = false;
        // find an emtpy tile in current room to put it in
        for (int y = currentRoomFlags.topLeftY; y < currentRoomFlags.width; y++){
            for (int x = currentRoomFlags.topLeftX; x < currentRoomFlags.hight; x++){
                if (castleMap[y][x].itemInTile.name == "Empty"){
                    castleMap[y][x].itemInTile = player.itemsInInventory[i]; // put item in tile
                    giveTileItem = true;
                }
                break;
            }
            if (giveTileItem){
                break;
            }
        }
        player.itemsInInventory.erase(player.itemsInInventory.begin()+i); // remove the item for player inventory
        printString(miscResponses[12]);
    } else {
        printString(miscResponses[2]); // we messed up
    }
}