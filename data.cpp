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

char roomDescriptionMessages[][50] = {
    ". ",
    "You enter the ",
    "You enter a ",
    "The room is %ix%i. "
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

// Differnt room types and their corresponding numbers
// 0 is the defalt
roomType roomTypes[] = {
    {"Unused", "", false}, // 0
    {"King's bedroom", "An almost sacred room only to be tread in the most necessary of times.", true}, // 1
    {"kitchen", "A room full of wondrous smells where food fit for kings (of course) is made.", true}, // 2
    {"storeroom", "A stuffed room which houses everything from food to spare sheets.", true}, // 3
    {"dinning room", "A large room with an even larger table in the middle.", true}, // 4
    {"servants corridor", "A cramped room in which you can sleep, eat or even just take a break without getting yelled at.", true}, // 5
    {"game room", "A cheery room were the sounds of chatter and fun echo off the walls.", false}, // 6
    {"music room", "A loud room were songs, melodies, and ballads can be heard.", false}, // 7
    {"library", "A quiet, calming room filled with shelves of books.", false}, // 8
    {"armory", "A somber room filled with polished swords, shields and other metal objects.", false}, // 9
    {"treasure room", "A windowless room with mountains of gold, piles of loot and heaps of riches.", false}, // 10
    {"hall", "A long narrow passage used to connect more important rooms.", false} // 11
};