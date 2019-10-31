#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

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

string genCurrentRoomThingList(bool showItems){
    vector<string> thingsInRoom;
    string message;
    vector<string> messageArray;
    vector<int> wordOccurrence;
    bool exists;
    int i;
    if (showItems){
        for (i = 0; i < currentRoomFlags.itemsInRoom.size(); i++){
            thingsInRoom.push_back(currentRoomFlags.itemsInRoom[i].name);
        }
    } else {
        for (i = 0; i < currentRoomFlags.furnitureInRoom.size(); i++){
            thingsInRoom.push_back(currentRoomFlags.furnitureInRoom[i].name);
        }
    }

    for (i = 0; i < thingsInRoom.size(); i++){
        exists = false;
        for (int j = 0; j < messageArray.size(); j++){
            if (thingsInRoom[i] == messageArray[j]){
                wordOccurrence[j]++;
                exists = true;
                break;
            }
        }
        if(!exists){
            messageArray.push_back(thingsInRoom[i]);
            wordOccurrence.push_back(1);
        }
    }
    for (i = 0; i < messageArray.size(); i++){
        message.append(to_string(wordOccurrence[i]));
        message.append(" ");
        message.append(messageArray[i]);
        if (wordOccurrence[i] != 1){
            message.append("s");
        }
        if (i != messageArray.size() - 1){
            message.append("\n");
        }
    }
    if (i == 0){
        if (showItems){
            message = "There are no items in this room.";
        } else {
            message = "There is no furniture in this room.";
        }
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
        printString(genCurrentRoomThingList(true));
        gameFlags.printCurrentRoomItems = false;
    }
    if (gameFlags.printCurrentRoomFurniture){
        printString(genCurrentRoomThingList(false));
        gameFlags.printCurrentRoomFurniture = false;
    }
}