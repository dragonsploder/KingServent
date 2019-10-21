#include <string>

#include "KingServent.h"

using namespace std;

// Materials used in defining properties of items and furniture
string materials[] = {
    "wood",
    "metal",
    "copper"
};

// Tile type
string tileType[] = {
    "Floor",
    "Wall",
    "Door"
};

// Int to direction convertion array
string directions[] = {
    "None",
    "North",
    "East",
    "South",
    "West"
};

// Strings used in the door message
string doorMessages[] = {
    "There is ",
    "a doorway to the north, ",
    "a doorway to the east, ",
    "a doorway to the south, ",
    "a doorway to the west, ",
    "a doorway to the north. ",
    "a doorway to the east.",
    "a doorway to the south.",
    "a doorway to the west.",
    "and "
};

// Strings that had no other home
string miscResponses[] = {
    "I didn't understand that",
    ">",
    "Developer Error",
    "You can't do that right now",
    "Are you sure you want to exit?",
    "Ok"
};

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
string commands[9][10] = {
    {"Reserved"},
    {"look",  "l", "lk"},
    {"north", "n", "nth"},
    {"east", "e", "est"},
    {"south", "s", "sth"},
    {"west", "w", "wst"},
    {"quit", "exit"},
    {"yes"},
    {"no"}
};