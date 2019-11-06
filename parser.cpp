#include <string>
#include <iostream>
#include <cctype>
#include <sstream>

#include "KingServent.h"

using namespace std;

string turnLowerCase(string input){ // turn a string to all lower case letters
    for (int j = 0; j < input.size(); j++){ // for every letter
        input[j] = tolower(input[j]); // make it lower case
    }
    return input;
}

// Get user input, return corresponding number
int getInput(){
    string rawinput; // The string input
    string input[4] = { // The user can input upto four words
        "None",
        "None",
        "None",
        "None"
    };
    int command = 0; // number equivalent of the command
    do {
        do {
            printString(miscResponses[1], false); // ">"
            getline(cin, rawinput); // Get input
        } while (rawinput.empty()); // Do it again if the user just hits enter

        rawinput = turnLowerCase(rawinput); // Make lower case

        stringstream ssin(rawinput);
        for(int i = 0; ssin.good() && i < 4; ++i){
            ssin >> input[i]; // split rawinput at spaces into input
        }

        for (int i = 0; i < (sizeof(commands)/sizeof(commands[0])); i++){ // For every possible command
            for (int j = 0; j < (sizeof(commands[i])/sizeof(commands[i][0])); j++){ // For every command permutation
                if (input[0] == commands[i][j]){ // If input is equal to command
                    command = i; // Make command equal to location in commands array
                    break;
                }
            }
        }

        if (command == 0){
            printString(miscResponses[0]); // Tell the user they inputted an invalid command
        }
    } while (command == 0); // While a valid command use not been inputted
    gameFlags.input[0] = input[0]; // update gameFlags.input so input can be accessed anywere
    gameFlags.input[1] = input[1];
    gameFlags.input[2] = input[2];
    gameFlags.input[3] = input[3];
    return command;
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

bool isValidInput(int input){
    string lowerCaseName; // Used when commparing strings so uppercase letters dont mess anything up
    string userObjectName; // Concat user input into one string
    switch (input){
        case 1: // look
            if (gameFlags.input[1] == "None" || gameFlags.input[1] == "items" || gameFlags.input[1] == "i" || gameFlags.input[1] == "furniture" || gameFlags.input[1] == "f"){ // Check for secondary keywords furniture and items 
                return true;
            }
            break;
        case 6: // Can always quit
        case 10: // Cn always acceses inventory
            return true;
        case 2: // north
        case 3: // east
        case 4: // south
        case 5: // west
            for (int i = 0; i < currentRoomFlags.doors.size(); i++){ // For every door in room
                if (currentRoomFlags.doors[i][2] == input - 1){ // If the one of the doors is the same as the input
                    return true;
                }
            }
            break;
        case 9: // examine item / furniture / item in inventory
            if (gameFlags.input[1] == "None") { // Didn't give an object to examine
                printString(miscResponses[6]);
                return false;
            } 

            userObjectName.append(gameFlags.input[1]); // Concat the input for two words (e.g. chicken egg)
            if (gameFlags.input[2] != "None"){
                userObjectName.append(" ");
                userObjectName.append(gameFlags.input[2]);
            }
            if (gameFlags.input[3] != "None"){
                userObjectName.append(" ");
                userObjectName.append(gameFlags.input[3]);
            }

            for (int i = 0; i < currentRoomFlags.itemsInRoom.size(); i++){ // for every item in current room
                lowerCaseName = turnLowerCase(currentRoomFlags.itemsInRoom[i].name); // make the name lowercase (e.g. Shirt --> shirt)
                if (userObjectName == lowerCaseName){ // if one of the items is the same as input
                    gameFlags.input[1] = currentRoomFlags.itemsInRoom[i].name; // from now on we just want to use input[1], so put whole name there
                    return true;
                }
            }
            for (int i = 0; i < currentRoomFlags.furnitureInRoom.size(); i++){ // same as items but for furniture
                lowerCaseName = turnLowerCase(currentRoomFlags.furnitureInRoom[i].name);
                if (userObjectName == lowerCaseName){
                    gameFlags.input[1] = currentRoomFlags.furnitureInRoom[i].name;
                    return true;
                }
            }
            for (int i = 0; i < player.itemsInInventory.size(); i++){ // same as before but for items in inventory
                lowerCaseName = turnLowerCase(player.itemsInInventory[i].name);
                if (userObjectName == lowerCaseName){
                    gameFlags.input[1] = player.itemsInInventory[i].name;
                    return true;
                }
            }
            for (int i = 0; i < player.elementaryItemsInInventory.size(); i++){ // same as before but for elementaryitems
                lowerCaseName = turnLowerCase(player.elementaryItemsInInventory[i].name);
                if (userObjectName == lowerCaseName){
                    gameFlags.input[1] = player.elementaryItemsInInventory[i].name;
                    return true;
                }
            }
            // if we got here, the object is not present
            printString(miscResponses[7], false);
            printString(userObjectName, false);
            printString(miscResponses[8]);
            return false;
        case 11: // get an item
            if (gameFlags.input[1] == "None") { // Didn't give an items to get
                printString(miscResponses[9]);
                return false;
            }
            userObjectName.append(gameFlags.input[1]); // same as in examine
            if (gameFlags.input[2] != "None"){
                userObjectName.append(" ");
                userObjectName.append(gameFlags.input[2]);
            }
            if (gameFlags.input[3] != "None"){
                userObjectName.append(" ");
                userObjectName.append(gameFlags.input[3]);
            }

            for (int i = 0; i < currentRoomFlags.itemsInRoom.size(); i++){ // for every item in the room
                lowerCaseName = turnLowerCase(currentRoomFlags.itemsInRoom[i].name); // turn to lowercase to avoid confution
                if (userObjectName == lowerCaseName){ // the item exists
                    if (canGetItemOfSize(currentRoomFlags.itemsInRoom[i].size)){ // the player has room to pick the item up
                        gameFlags.input[1] = currentRoomFlags.itemsInRoom[i].name; // put full name into input[1]
                        return true;
                    } else { // player can't carry it
                        printString(miscResponses[13]); 
                        return false;
                    }
                }
            }

            for (int i = 0; i < currentRoomFlags.furnitureInRoom.size(); i++){ // just a quick check for furniter so we can tell the player directly they can pick it up
                lowerCaseName = currentRoomFlags.furnitureInRoom[i].name;
                for (int j = 0; j < lowerCaseName.size(); j++){
                    lowerCaseName[j] = tolower(lowerCaseName[j]);
                }
                if (userObjectName == lowerCaseName){
                    printString(miscResponses[10]);
                    return false;
                }
            }
            printString(miscResponses[7], false);
            printString(userObjectName, false);
            printString(miscResponses[8]);
            return false;
        case 12: // drop item
            if (gameFlags.input[1] == "None") { // no item provided
                printString(miscResponses[9]);
                return false;
            }
            userObjectName.append(gameFlags.input[1]); // same as in "examen"
            if (gameFlags.input[2] != "None"){
                userObjectName.append(" ");
                userObjectName.append(gameFlags.input[2]);
            }
            if (gameFlags.input[3] != "None"){
                userObjectName.append(" ");
                userObjectName.append(gameFlags.input[3]);
            }
            for (int i = 0; i < player.itemsInInventory.size(); i++){ // for every item in inventory
                lowerCaseName = turnLowerCase(player.itemsInInventory[i].name); // lowercase, we know the drill
                if (userObjectName == lowerCaseName){
                    gameFlags.input[1] = player.itemsInInventory[i].name;
                    if (currentRoomFlags.itemsInRoom.size() >= (currentRoomFlags.width * currentRoomFlags.hight)) {
                        printString(miscResponses[14]);
                        return false;
                    }
                    return true;
                }
            }
            printString("There is no ", false);
            printString(userObjectName, false);
            printString(" in your inventory.");
            return false;
        default:
            printString(miscResponses[2]); // somthing bad happend
    }
    printString(miscResponses[3]); // generic fall through respons
    return false;
}