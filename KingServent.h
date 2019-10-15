#include <string>
#include <vector>


#ifndef KING_H
#define KING_H

#define CASTLE_WIDTH 40 //Width of the castle 
#define CASTLE_HIGHT 40 // Hight of the castle
#define ROOM_ITERATIONS 3 // Number of times the BSP system will split the rooms

struct Furniture { // Furniture has a:
    std::string name;
    std::string discription;
    int material;
    int size;
};

struct Item { // An Item has a:
    std::string name;
    std::string discription;
    int material;
    int size;
};

struct People { // People have a:
    std::string name;
    std::string discription;
    int socialClass;
    int age;
};

struct Tile { // Every tile of the castle has a:
    std::string name;
    std::string discription;
    Furniture funitureInTile; // A tile can only have one piece of furniture
    People personInTile; // A tile can only have one person
    std::vector<Item> itemsInTile; // A tile can have multipe items

    int type; // Floor, door, wall, ect
    bool explored = false; // Has the player been here
    bool floodFlag = false; // Used in floodFill()
    bool isCurrentPlayerLocation = false; // Does the player occupy this tile
    bool isOpen = false; // Used if tile is a door 
    int X; // This tile's x on the catle
    int Y; // This tile's y on the catle
};

struct Player { // A player has:
    std::string name;
    std::string discription;
    Tile currentLocation;
    int X; // Current location X
    int Y; // Current location X
};

struct RoomLocationFlags { // Information about a room
    std::vector<People> peopleInRoom; // Who is in this room
    std::vector<Item> itemsInRoom; // What items are in this room
    std::vector<Furniture> furnitureInRoom; // What furniture is in this room

    std::vector<std::vector<int> > doors; // Were are the doways
                                          // Format (y, x, direction)
                                          // Direction is 1-4 corresponding to north, east, south, west respectivly

    int hight; // Hight of the room
    int width; // Width of the room
};

// main
extern Player player; // "The" plyer
extern RoomLocationFlags currentRoomFlags; // Room flags for the room the player is in
// END main

// castleGen
extern std::vector<std::vector<int> > basicMapMatrix; // Map used by BSP system for generating castle map
extern std::vector< std::vector<Tile> > castleMap; // Actual castle map, full of Tiles
void genCastle(); // Function which generats a map and filles castleMap
// END castleGen

// misc
void copyMatrix(std::vector<std::vector<int> > &basicMatrix, std::vector< std::vector<Tile> > &mapMatrix); // Copy a matrix of ints to a matrix of tiles
void setTileLocations(std::vector< std::vector<Tile> > &mapMatrix); // Connect each Tile with X and Y values
void resetFloodFlag(); // Set all of the tiles floodFlag to false
void printString(std::string message); // Print a string to the screen
// END misc

// data
extern std::string materials[]; // String array of materials
extern std::string tileType[]; // String array of tile types (e.g. door, wall, ect)
extern std::string directions[]; // String array of directions n,e,s,w
extern std::string doorMessages[];
// END data

// room 
void updateRoomFlags(); // Update Room Flages for the room the player is currently in
// END room

// player
std::string genPlayerEnterRoomMessage(); // Generat the message the player gets upon entering a room
// END player


#endif