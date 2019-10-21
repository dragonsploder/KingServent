#include <string>
#include <iostream>
#include <cctype>

#include "KingServent.h"

using namespace std;

// Get user input, return corresponding number
int getInput(){
    string input; //
    int command = 0;
    do {
        do {
            printString(miscResponses[1], false); // ">"
            getline(cin, input); // Get input
        } while (input.empty()); // Do it agian if the user just hits enter

        for (int i = 0; i < input.size(); i++){ // For every letter in input
            input[i] = tolower(input[i]); // Make lower case
        }
        for (int i = 0; i < (sizeof(commands)/sizeof(commands[0])); i++){ // For every possible command
            for (int j = 0; j < (sizeof(commands[i])/sizeof(commands[i][0])); j++){ // For every command permutation
                if (input == commands[i][j]){ // If input is equal to command
                    command = i; // Make command equal to location in commands array
                    break;
                }
            }
        }
        if (command == 0){
            printString(miscResponses[0]);
        }
    } while (command == 0); // While a valid command use not been inputed
    return command;
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

bool isValidInput(int input){
    switch (input){
        case 1:
        case 6:
            return true;
        case 2:
        case 3:
        case 4:
        case 5:
            for (int i = 0; i < currentRoomFlags.doors.size(); i++){
                if (currentRoomFlags.doors[i][2] == input - 1){
                    return true;
                }
            }
            break;
        default:
            printString(miscResponses[2]);
    }
    printString(miscResponses[3]);
    return false;
}