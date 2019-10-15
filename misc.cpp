#include <vector>
#include <iostream>
#include <string>
#include <stdio.h>

#include "KingServent.h"

using namespace std;

// Copy a matrix of ints to a matrix of tiles 
void copyMatrix(vector<vector<int> > &basicMatrix, vector< vector<Tile> > &mapMatrix){
    for(int y = 0; y < mapMatrix.size(); y++){ // For the "y" values in the matrices
        for(int x = 0; x < mapMatrix[0].size(); x++){ // For the "x" values in the matrices
            mapMatrix[y][x].type = basicMatrix[y][x]; // Tile type at y, x is equal to y, x of basicMatrix
        }
    }
}

// Connect each Tile with X and Y values
void setTileLocations(vector< vector<Tile> > &mapMatrix){
    for(int y = 0; y < mapMatrix.size(); y++){ // For the "y" values in the mapMatrix
        for(int x = 0; x < mapMatrix[0].size(); x++){ // For the "x" values in the mapMatrix
            mapMatrix[y][x].X = x; // Tile X at y, x is equal to x
            mapMatrix[y][x].Y = y; // Tile Y at y, x is equal to y
        }
    }
}

// Set all of the tiles floodFlag to false
void resetFloodFlag(){
    for(int y = 0; y < CASTLE_HIGHT; y++){
        for(int x = 0; x < CASTLE_WIDTH; x++){
            castleMap[y][x].floodFlag = false;
        }
    }
}

// Print a string to the screen
void printString(string message){
    cout << message << endl;
}