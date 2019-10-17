#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <tgmath.h>
#include <cstring>

#include "KingServent.h"

using namespace std;

vector< vector<Tile> > castleMap(CASTLE_HIGHT, vector<Tile>(CASTLE_WIDTH)); // Actual castle map, full of Tiles
vector<vector<int> > basicMapMatrix(CASTLE_HIGHT, vector<int>(CASTLE_WIDTH,0)); // Map used by BSP system for generating castle map

// Function used to print castleMap to screen
void printMap(vector< vector<Tile> > &castleMap){
    for (int h = 0; h < castleMap.size(); h++){ // For "h" in castleMap
        for (int w = 0; w < castleMap[0].size(); w++){ // For "w" in castleMap
            if (castleMap[h][w].isCurrentPlayerLocation){ // If player location
                printf("@");
            } else if (tileType[castleMap[h][w].type] == "Floor"){ // If Floor
                printf(".");
            } else if (tileType[castleMap[h][w].type] == "Wall"){ // If Wall
                printf("#");
            } else if (tileType[castleMap[h][w].type] == "Door"){ // If Door
                if (castleMap[h][w].isOpen){ // Is the door oepn
                    printf("\'");
                } else {
                    printf("+");
                }
            } else { // Cach statement for debugging
                printf("!");
            }
        }
        printf("\n"); // New line after each row
    }
}

// A big function which generates castleMap rooms
/**
 * The basic idea for this generator is a BSP (or Binary Space Partitioning) system.
 * The function starts with one room which it randomly splits in half
 * It does this several times until a desierd amount of rooms have been created
 * Each room is connected to its "split partner" with a door
**/
// Iteration is how many times every room will be split
// FullWalls adds an outline
// MinWallDist is the minimun size of a room
void binarySpacePartitioning(vector<vector<int> > &mapMatrix, int iterations, bool fullWalls, int minWallDist){
    int hight = mapMatrix.size() - 1; 
    int width = mapMatrix[0].size() - 1;
    // This function works by keeping track of the coordinates of a room (four to be exact) and were doors should be
                                                // (x1,y1,x2,y2)
    vector<vector<int> > roomCoordinates; // List of rooms
    vector<vector<int> > newRoomCoordinates; // List which gets filled with the splits of roomCoordinates
    vector<vector<int> > connectionsYaxis; // Horizontal doors
                                           // (y, minX, maxX)
    vector<vector<int> > connectionsXaxis; // Vertical doors
                                           // (x, minY, maxY)

    //Format = X1,Y1,X2,Y2
    roomCoordinates.push_back({0, 0, width, hight}); // Start with a room the size of the matrix
    for (int i = 0; i < iterations; i++){ // For Each iteration
        for (int room = 0; room < roomCoordinates.size(); room++){ // For each room
            int roomWidth = (roomCoordinates[room][2] - roomCoordinates[room][0]);
            int roomHight = (roomCoordinates[room][3] - roomCoordinates[room][1]);

            int r = rand() % (roomHight + roomWidth); // Horizontal or vertical line, based on how much space there is (i.e. a long horizonl room is more likely to get a vertical lin)

            if (r <= roomHight){ // Horizontal split
                if ((minWallDist + 1) * 2 < roomHight && roomHight >= 4){
                    int lineY = (rand() % (roomHight - (2 * minWallDist))) + minWallDist; // Where is the room split

                    connectionsYaxis.push_back({lineY + roomCoordinates[room][1], roomCoordinates[room][0], roomCoordinates[room][2]}); // Where the door can go

                    // The two new rooms
                    newRoomCoordinates.push_back({roomCoordinates[room][0], roomCoordinates[room][1], roomWidth + roomCoordinates[room][0], lineY + roomCoordinates[room][1]});
                    newRoomCoordinates.push_back({roomCoordinates[room][0], lineY + roomCoordinates[room][1], roomWidth + roomCoordinates[room][0], roomHight + roomCoordinates[room][1]});
                } else { // If this room is two small to split, put it back
                    newRoomCoordinates.push_back({roomCoordinates[room][0], roomCoordinates[room][1], roomCoordinates[room][2], roomCoordinates[room][3]});
                }
            } else { // Vertical split
                if ((minWallDist + 1) * 2 < roomWidth && roomWidth >= 4){
                    int lineX = (rand() % (roomWidth - (2 * minWallDist))) + minWallDist; // Where is the room split

                    connectionsXaxis.push_back({lineX + roomCoordinates[room][0], roomCoordinates[room][1], roomCoordinates[room][3]}); // Where the door can go

                    // The two new rooms
                    newRoomCoordinates.push_back({roomCoordinates[room][0], roomCoordinates[room][1], lineX + roomCoordinates[room][0], roomHight + roomCoordinates[room][1]});
                    newRoomCoordinates.push_back({lineX + roomCoordinates[room][0], roomCoordinates[room][1], roomWidth + roomCoordinates[room][0], roomHight + roomCoordinates[room][1]});
                
                } else { // If this room is two small to split, put it back
                    newRoomCoordinates.push_back({roomCoordinates[room][0], roomCoordinates[room][1], roomCoordinates[room][2], roomCoordinates[room][3]});
                }
            }
        }
        roomCoordinates.clear(); // Get rid of the old rooms
        for (int i = 0; i < newRoomCoordinates.size(); i++){ // Save the new rooms
            roomCoordinates.push_back(newRoomCoordinates[i]);
        }
        newRoomCoordinates.clear(); // Clear space for the next iteration of rooms
    }
    if (fullWalls){ 
        roomCoordinates.push_back({0, 0, width, hight}); // Add an outline
    }

    // Fill mapMatrix
    for (int room = 0; room < roomCoordinates.size(); room++){ // For every room
        int x1 = roomCoordinates[room][0];
        int y1 = roomCoordinates[room][1];
        int x2 = roomCoordinates[room][2];
        int y2 = roomCoordinates[room][3];

        for (int i = x1; i <= x2; i++){ // Top horizontal line
            mapMatrix[y1][i] = 1; // Make floor into wall
        }
        for (int i = y1; i <= y2; i++){ // Left vertical line
            mapMatrix[i][x1] = 1; // Make floor into wall
        }
        for (int i = x1; i <= x2; i++){ // Bottom horizontal line
            mapMatrix[y2][i] = 1; // Make floor into wall
        }
        for (int i = y1; i <= y2; i++){ // Right vertical line
            mapMatrix[i][x2] = 1; // Make floor into wall
        }
    }

    // Add doors
    for (int y = 0; y < connectionsYaxis.size(); y++){// For every door on the Yaxis
        bool flag = true;
        do {
            int foo = (rand() % (connectionsYaxis[y][2] - connectionsYaxis[y][1] - 1)) + 1; // Randomly pick numbers
            foo += connectionsYaxis[y][1]; // Offset by room location
            /** Check for this case
             * #########
             * #  #    #
             * ###+#####
            **/
            if (mapMatrix[connectionsYaxis[y][0] + 1][foo] == 0 && mapMatrix[connectionsYaxis[y][0] - 1][foo] == 0){ 
                mapMatrix[connectionsYaxis[y][0]][foo] = 2; // Make that location a door
                flag = false; // Stop trying random locations
            }
        } while (flag); // While we haven't found a good location
    }

    // Same as above
    for (int x = 0; x < connectionsXaxis.size(); x++){
        bool flag = true;
        do {
            int foo = (rand() % (connectionsXaxis[x][2] - connectionsXaxis[x][1] - 1)) + 1;
            foo += connectionsXaxis[x][1]; 
            if (mapMatrix[foo][connectionsXaxis[x][0] + 1] == 0 && mapMatrix[foo][connectionsXaxis[x][0] - 1] == 0){
                mapMatrix[foo][connectionsXaxis[x][0]] = 2;
                flag = false;
            }
        } while (flag);
    }    
}

// Put the player on the map
void placePlayer(vector< vector<Tile> > &castleMap){
    bool flag = true;
    do {
        int tempX = rand() % (CASTLE_WIDTH - 1);
        int tempY = rand() % (CASTLE_HIGHT - 1);
        if (tileType[castleMap[tempY][tempX].type] == "Floor"){ // Is this a location the player can exist on
            player.X = tempX; // Set player X
            player.Y = tempY; // Set player Y
            castleMap[tempY][tempX].isCurrentPlayerLocation = true; // Set this tile's isCurrentPlayerLocation 
            flag = false; // Stop trying random locations
        }
    } while(flag); // While we haven't found a good location
}

void genCastle(){
    if (seed == 0){
        srand(time(NULL)); // Set rand seed
        printf("Seed:%i\n", time(NULL)); // Testing 
    } else {
        srand(seed); // Set rand seed
        printf("Seed:%i\n", seed); // Testing   
    }
    binarySpacePartitioning(basicMapMatrix, ROOM_ITERATIONS, true, 2); // Generate rooms
    copyMatrix(basicMapMatrix, castleMap); // Copy basicMapMatrix onto castleMap
    vector<vector<int> >().swap(basicMapMatrix); // Hack to release basicMapMatrix
    placePlayer(castleMap);
    setTileLocations(castleMap); 
}