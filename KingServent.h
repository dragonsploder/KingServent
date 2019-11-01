#include <string>
#include <vector>


#ifndef KING_H
#define KING_H

#define CASTLE_WIDTH 40 //Width of the castle 
#define CASTLE_HIGHT 40 // Hight of the castle
#define ROOM_ITERATIONS 3 // Number of times the BSP system will split the rooms
#define PUT_THING_IN_ROOM 15 // 1 out of n chance for every tile
#define ITEM_CAP 7 // 1 out of n chance for every tile

struct ElementaryItem { // Unbreackable base item 
    std::string name;
    std::string description;
    bool liquid;
};

struct Item { // An item made fromm ElementaryItem
    std::string name;
    std::string description;
    std::vector<ElementaryItem> parts;
    int integrity;
    int size;
};

extern Item emptyItem;

struct Furniture { // Furniture has a:
    std::string name;
    std::string description;
    int typeOfContainer;
    std::vector<Item> itemsContained = {};
};

extern Furniture emptyFurniture;

struct People { // People have a:
    std::string name;
    std::string description;
    int X; // Current location X
    int Y; // Current location X
    int socialClass;
    int age;
};

extern People emptyPerson;

struct Tile { // Every tile of the castle has a:
    std::string name;
    std::string description;
    Furniture funitureInTile = emptyFurniture; // A tile can only have one piece of furniture
    People personInTile = emptyPerson; // A tile can only have one person
    Item itemInTile = emptyItem; // A tile can have one item

    int type; // Floor, door, wall, ect
    int roomType = 0; // Type of room
    //bool explored = false; // Has the player been here
    bool floodFlag = false; // Used in floodFill()
    bool isCurrentPlayerLocation = false; // Does the player occupy this tile
    bool isOpen = false; // Used if tile is a door 
    int X; // This tile's x on the castle
    int Y; // This tile's y on the castle
};

struct GameFlags { // flags used to tell the game what to do
    std::string input[4]; 
    bool printNewRoomMessage = false; // Have we entered a new room
    bool printCurrentRoomDescription = false; // Do we want to see our surroundings
    bool printCurrentRoomItems = false; // What items are in this room
    bool printCurrentRoomFurniture = false; // What furniture is in this room
};

struct RoomLocationFlags { // Information about a room
    std::vector<People> peopleInRoom; // Who is in this room
    std::vector<Item> itemsInRoom; // What items are in this room
    std::vector<Furniture> furnitureInRoom; // What furniture is in this room

    std::vector<std::vector<int> > doors; // Were are the doorways
                                          // Format (y, x, direction)
                                          // Direction is 1-4 corresponding to north, east, south, west respectively

    int hight; // Hight of the room
    int width; // Width of the room
    int roomType = 0; // What kind of room is this
};

struct RoomType {
    std::string name;
    std::string description;

    bool mandatory;
};

struct RoomFilling { // What items go in what rooms
    Item mandatoryItem;
    std::vector<Item> possibleItems;

    Furniture mandatoryFurniture;
    std::vector<Furniture> possibleFurniture;
};

// main
extern People player; // "The" plyer
extern RoomLocationFlags currentRoomFlags; // Room flags for the room the player is in
extern GameFlags gameFlags; // What messages to print
extern int seed; // Used to set the seed
// END main

// castleGen
extern std::vector<std::vector<int> > basicMapMatrix; // Map used by BSP system for generating castle map
extern std::vector< std::vector<Tile> > castleMap; // Actual castle map, full of Tiles
void genCastle(); // Function which generats a map and filles castleMap
void printMap(); // Prints out the castle
// END castleGen

// misc
void copyMatrix(std::vector<std::vector<int> > &basicMatrix, std::vector< std::vector<Tile> > &mapMatrix); // Copy a matrix of ints to a matrix of tiles
void setTileLocations(std::vector< std::vector<Tile> > &mapMatrix); // Connect each Tile with X and Y values
void resetFloodFlag(); // Set all of the tiles floodFlag to false
void printString(std::string message, bool endline = true); // Print a string to the screen
// END misc

// data
extern std::string tileType[]; // String array of tile types (e.g. door, wall, ect)
extern std::string directions[]; // String array of directions n,e,s,w
extern char roomDescriptionMessages[][50];
extern std::string doorMessages[]; // String array of messages used to discribe doorways
extern std::string miscResponses[]; // Strings that had no other home
extern const std::string commands[10][10]; // String array of possible commands
extern RoomType roomTypes[12]; // Differnt room types and their corresponding numbers
extern const RoomFilling roomFilling[12]; // What to put in those rooms
// END data

// room 
void updateRoomFlags(); // Update Room Flages for the room the player is currently in
// END room

// player
void executeCommand(int command); // Execute a command
// END player

// messages
/*std::string genPlayerEnterRoomMessage(); // Generat the message the player gets upon entering a room
std::string genCurrentRoomDescription(); // What dose the current room look like*/
void printMessages(); // They player did something, tell them what happend
// END messages

// parser
int getInput(); // Get input from the player
bool isValidInput(int input); // Cheak if player can perform an command
// END parser


#endif