#include <string>

#include "KingServent.h"

using namespace std;

void movePlayer(int Y, int X){
    castleMap[player.Y][player.X].isCurrentPlayerLocation = false;
    player.Y = Y;
    player.X = X;
    castleMap[player.Y][player.X].isCurrentPlayerLocation = true;
}

/**
 * Input commands are all connected to a number:
 * 0: Reserved
 * 1: "Look" - Used to examine surroundings  
 * 2: "North" - Go north
 * 3: "East" - Go east
 * 4: "South" - Go south
 * 5: "West" - Go west
 * 6: "Quit" - Quit the game
 * 7: "Yes"
 * 8: "No"
**/
void executeCommand(int command){
    if (command == 1){
        if (gameFlags.input[1] == "None"){
            gameFlags.printCurrentRoomDescription = true;
        } else if (gameFlags.input[1] == "items"){
            gameFlags.printCurrentRoomItems = true;
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
    } else {
        printString(miscResponses[2]);
    }
}