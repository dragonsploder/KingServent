#include <string>

#include "KingServent.h"

using namespace std;

// Generate a message for the prayer upon entering the room
string genPlayerEnterRoomMessage(){
    string message; // string for compleat message

    if (currentRoomFlags.roomType == 11) { // "You enter ..."
        message.append(roomDescriptionMessages[2]); // It's a hall so use "a"
    } else {
        message.append(roomDescriptionMessages[1]); // Everything else use "the"
    }
    message.append(roomTypes[currentRoomFlags.roomType].name);
    message.append(roomDescriptionMessages[0]); // End the message

    // Room Size
    char tempMessage[50]; // Buffer for room size message
    sprintf(tempMessage, roomDescriptionMessages[3], currentRoomFlags.width, currentRoomFlags.hight); // fill tempMessage with "The room is [room width]x[room hight]"
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
    return roomTypes[currentRoomFlags.roomType].description;
}

string genCurrentRoomItemList(){
    string message;
    int i;
    for (i = 0; i < currentRoomFlags.itemsInRoom.size(); i++){
        message.append(currentRoomFlags.itemsInRoom[i].name);
        if (i != currentRoomFlags.itemsInRoom.size() - 1){
            message.append("\n");
        }
    }
    if (i == 0){
        message = "There are no items in this room.";
    }
    return message;
}

string genCurrentRoomFurnitureList(){
    string message;
    int i;
    for (i = 0; i < currentRoomFlags.furnitureInRoom.size(); i++){
        message.append(currentRoomFlags.furnitureInRoom[i].name);
        if (i != currentRoomFlags.furnitureInRoom.size() - 1){
            message.append("\n");
        }
    }
    if (i == 0){
        message = "There is no furniture in this room.";
    }
    return message;
}

void printMessages(){
    if (gameFlags.printNewRoomMessage){
        printString(genPlayerEnterRoomMessage()); // Print out a message describing room
        gameFlags.printNewRoomMessage = false;
    }
    if (gameFlags.printCurrentRoomDescription){
        printString(genCurrentRoomDescription());
        gameFlags.printCurrentRoomDescription = false;
    }
    if (gameFlags.printCurrentRoomItems){
        printString(genCurrentRoomItemList());
        gameFlags.printCurrentRoomItems = false;
    }
    if (gameFlags.printCurrentRoomFurniture){
        printString(genCurrentRoomFurnitureList());
        gameFlags.printCurrentRoomFurniture = false;
    }
}