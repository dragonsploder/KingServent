#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

#include "KingServent.h"

using namespace std;

// turn away of strings into format:
/*
 * 1 Book
 * 2 Candles
 * ect
**/
string compressMessage(vector<string> things){ 
    string message; // end message
    vector<string> messageArray; // array of non repeating strings
    vector<int> wordOccurrence; // how many times a word occurs
    bool exists; // Dose a word already exist
    
    for (int i = 0; i < things.size(); i++){ // for every word
        exists = false;
        for (int j = 0; j < messageArray.size(); j++){ // for every previous word
            if (things[i] == messageArray[j]){ // is this a repeating word
                wordOccurrence[j]++; // increas count for word
                exists = true;
                break;
            }
        }
        if(!exists){ // If the word doesn't exists
            messageArray.push_back(things[i]);
            wordOccurrence.push_back(1);
        }
    }
    for (int i = 0; i < messageArray.size(); i++){ // For every word
        message.append(to_string(wordOccurrence[i])); // How many times the word appeared
        message.append(" ");
        message.append(messageArray[i]); // The word
        if (wordOccurrence[i] != 1){ // If the word accours more then once
            message.append("s");
        }
        if (i != messageArray.size() - 1){ // For every word except the last
            message.append("\n");
        }
    }
    return message;
}

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
    return roomTypes[currentRoomFlags.roomType].description; // figurer it out
}

string genCurrentRoomThingList(bool showItems){
    vector<string> thingsInRoom; // array so I can swap for items - furniture
    string message; // end message
    if (showItems){ // Is this for items
        for (int i = 0; i < currentRoomFlags.itemsInRoom.size(); i++){
            thingsInRoom.push_back(currentRoomFlags.itemsInRoom[i].name); // use items
        }
    } else {
        for (int i = 0; i < currentRoomFlags.furnitureInRoom.size(); i++){
            thingsInRoom.push_back(currentRoomFlags.furnitureInRoom[i].name); // use furniture
        }
    }
    
    if (thingsInRoom.size() == 0){ // If there is nothing 
        if (showItems){
            message = "There are no items in this room.";
        } else {
            message = "There is no furniture in this room.";
        }
    } else {
        message = compressMessage(thingsInRoom); // make the message look nice
    }
    return message;
}

string genInventoryMessage(){
    string message; // end message
    vector<string> thingsInInventory; // vector to combined items and elementary items
    
    for (int i = 0; i < player.itemsInInventory.size(); i++){ // for every item in inventory
        thingsInInventory.push_back(player.itemsInInventory[i].name);
    }
    for (int i = 0; i < player.elementaryItemsInInventory.size(); i++){ // for every elementary item in inventory
        thingsInInventory.push_back(player.elementaryItemsInInventory[i].name);
    }

    if (player.elementaryItemsInInventory.size() + player.itemsInInventory.size() == 0){ // If the player doesn't have anything
        message = "There is nothing in your inventory.\n";
    } else { // make it look nice
        message = compressMessage(thingsInInventory);
    }
    return message;
}

void printMessages(){
    if (gameFlags.printNewRoomMessage){
        printString(genPlayerEnterRoomMessage()); // Print out a message giving specific room in game
        gameFlags.printNewRoomMessage = false;
    }
    if (gameFlags.printCurrentRoomDescription){
        printString(genCurrentRoomDescription()); // Print out a message describing generic room
        gameFlags.printCurrentRoomDescription = false;
    }
    if (gameFlags.printCurrentRoomItems){
        printString(genCurrentRoomThingList(true)); // Print out items in the room
        gameFlags.printCurrentRoomItems = false;
    }
    if (gameFlags.printCurrentRoomFurniture){
        printString(genCurrentRoomThingList(false)); // Print out furniture in room
        gameFlags.printCurrentRoomFurniture = false;
    }
    if (gameFlags.printInventory){
        printString(genInventoryMessage()); // Print out player inventory
        gameFlags.printInventory = false;
    }
}