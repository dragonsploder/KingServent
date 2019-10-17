#include <string>

#include "KingServent.h"

using namespace std;

// Generate a message for the prayer upon entering the room
string genPlayerEnterRoomMessage(){
    string message; // string for compleat message

    // Room Size
    char tempMessage[25]; // Buffer for room size message
    sprintf(tempMessage, "The room is %ix%i. ", currentRoomFlags.width, currentRoomFlags.hight); // fill tempMessage with "The room is [room width]x[room hight]"
    message.append(tempMessage); // Add room size message to main message

    // Door Messages
    message.append(doorMessages[0]); // Append "There is " to main message
    if (currentRoomFlags.doors.size() != 1) { // If there is more then one door, use list format
        for (int i = 1; i < currentRoomFlags.doors.size(); i++){ // For the each door except the first one.
            message.append(doorMessages[currentRoomFlags.doors[i][2]]); // Append "a doorway to the [north, south, east, west] "
            if (i == currentRoomFlags.doors.size() - 1){ // If this is the last door
                message.append(doorMessages[9]); // Append "and "
            }
        }
    }
    message.append(doorMessages[currentRoomFlags.doors[0][2] + 4]); // Append the last door (possible to be the only one) to main message
    // End Door Messages

    return message;

}

string genCurrentRoomDescription(){
    return "A room";
}

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
**/
void executeCommand(int command){
    if (command == 1){
        printString(genCurrentRoomDescription());
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
                updateRoomFlags();  // Floodfill the room the player is in and see whats in it
                printString(genPlayerEnterRoomMessage()); // Print out a message describing room
                break;
            }
        }
    } else {
        printString(miscResponses[2]);
    }
}