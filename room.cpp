


#include "KingServent.h"

// Variables used to find the width and hight of room
// Global b/c used by floodFill()
int lowestX;
int highestX;
int lowestY;
int highestY;

// Updates RoomData based on a Tile
void addRoomData(Tile tile){
    // Any people currently on the tile
    currentRoomFlags.peopleInRoom.push_back(tile.personInTile);
    // Any furniture currently on the tile
    currentRoomFlags.furnitureInRoom.push_back(tile.funitureInTile);
    // Any items currently on the tile (there can be more then one)
    for(int i = 0; i < tile.itemsInTile.size(); i++){
        currentRoomFlags.itemsInRoom.push_back(tile.itemsInTile[i]);
    }

    // Checks the four tiles next to this tile for a door
    // If there is one, it is pushed to currentRoomFlags in the format (Y, X, Direction)
    if (tileType[castleMap[tile.Y - 1][tile.X].type] == "Door"){
        currentRoomFlags.doors.push_back({tile.Y - 1, tile.X, 1}); // North
    }
    if (tileType[castleMap[tile.Y][tile.X + 1].type] == "Door"){
        currentRoomFlags.doors.push_back({tile.Y, tile.X + 1, 2}); // East
    }
    if (tileType[castleMap[tile.Y + 1][tile.X].type] == "Door"){
        currentRoomFlags.doors.push_back({tile.Y + 1, tile.X, 3}); // South
    }
    if (tileType[castleMap[tile.Y][tile.X - 1].type] == "Door"){
        currentRoomFlags.doors.push_back({tile.Y, tile.X - 1, 4}); // West
    }
}

// Calls addRoomData for each tile in the room, starting at (y, x)
// This is a recersive function
void floodFill(int y, int x){
    castleMap[y][x].floodFlag = true; // Sets this floodFlag so each tile is only "flooded" once
    addRoomData(castleMap[y][x]); // Calls addRoomData with current tile
    // If the tile to the [N,E,S,W] is a "Floor" and has not been "flooded"; 
    //     update [lowestY, highestX, highestY, lowestX] if necessary
    //     and call floodFill with that tile location
    if (tileType[castleMap[y - 1][x].type] == "Floor" && !castleMap[y - 1][x].floodFlag){ // North
        if (y - 1 < lowestY){ // If this is this new tile is farther north then all other tiles
            lowestY = y - 1; // Update lowestY
        }
        floodFill(y - 1, x); // Call floodFill for this new tile
    }
    if (tileType[castleMap[y][x + 1].type] == "Floor" && !castleMap[y][x + 1].floodFlag){ // East
        if (x + 1 > highestX){ // If this is this new tile is farther east then all other tiles
            highestX = x + 1; // Update highestX
        }
        floodFill(y, x + 1); // Call floodFill for this new tile
    }
    if (tileType[castleMap[y + 1][x].type] == "Floor" && !castleMap[y + 1][x].floodFlag){ // South
        if (y + 1 > highestY){ // If this is this new tile is farther south then all other tiles
            highestY = y + 1; // Update highestY
        }
        floodFill(y + 1, x); // Call floodFill for this new tile
    }
    if (tileType[castleMap[y][x - 1].type] == "Floor" && !castleMap[y][x - 1].floodFlag){ // West
        if (x - 1 < lowestX){ // If this is this new tile is farther west then all other tiles
            lowestX = x - 1; // Update lowestX
        }
        floodFill(y, x - 1); // Call floodFill for this new tile
    }
}

void updateRoomFlags(){
    lowestX = CASTLE_WIDTH; // Highest possible value of lowestX + 1
    highestX = 0; // Lowest possible value of highestX - 1
    lowestY = CASTLE_HIGHT; // Highest possible value of lowestY + 1
    highestY = 0; // Lowest possible value of highestX - 1
    floodFill(player.Y, player.X); // FloodFill from player (i.e. floodFill the current room)
    resetFloodFlag(); // Reset all floodFill flags so room can be flooded later
    currentRoomFlags.hight = highestY - lowestY + 1; // Find hight of room
    currentRoomFlags.width = highestX - lowestX + 1; // Find width of room
}