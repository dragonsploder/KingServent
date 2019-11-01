#include <string>

#include "KingServent.h"

using namespace std;

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
    "I didn't understand that", // 0
    ">", // 1
    "Developer Error", // 2
    "You can't do that right now", // 3
    "Are you sure you want to exit?", // 4
    "Ok", // 5
    "Examane what?", // 6
    "There is no ", // 7
    " in this room." // 8
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
 * 9: "Examane" - describe on abj.
**/
const string commands[10][10] = {
    {"Reserved"},
    {"look",  "l", "lk"},
    {"north", "n", "nth"},
    {"east", "e", "est"},
    {"south", "s", "sth"},
    {"west", "w", "wst"},
    {"quit", "exit"},
    {"yes"},
    {"no"},
    {"examane", "ex"}
};

// Unbreackable base item 
// Name: string
// Description: string
// Liquid: bool
const ElementaryItem elementaryItems[] = {
    {"Egg Shell", "A thin lay of protection for a growing animal.", false}, // 0
    {"Egg Yolk", "A slimy substance full of nutrients, or so I'm told.", true}, // 1
    {"Metal", "A typically hard, shinny, ductile material.", false}, // 2
    {"Wood", "Comes from a tree. A strong, light material.", false}, // 3
    {"Plastic", "Don't tell anyone, but it existed way before people thought.", false}, // 4
    {"Wax", "A moldable substance made by bees.", false}, // 5
    {"Wick", "A strip of a flamable material", false}, // 6
    {"Water", "A clear liquid used in almost everything, most notably life.", true}, // 7
    {"Cloth", "Woven fabric made form wool.", false}, // 8
    {"Ceramic", "Clay hardend from heat.", false}, // 9
    {"String", "A long thin cord.", false}, // 10
    {"Paper", "Thin sheets of wood pulp, not as weird as it sounds. Usually written on.", false}, // 11
    {"Leather", "Tanned animal skin, usually from a cow.", false}, // 12
    {"Gold", "A shiny, yellow precious metal.", false}, // 13
    {"Paint", "A liquid which comes in many different colors. Used in \"art\".", true}, // 14
    {"Cast iron", "A hard iron alloy.", false}, // 15
};
 
// An item made fromm ElementaryItem
// Name: string
// Description: string
// Vector of elementaryItems
// integrity: int 
//      1: Fall -> break
//      2: Hand -> break
//      3: Tool -> break
//      4: Magic -> break
//      5: Unbreakable 
// Size: int
//      0: No size (N/a)
//      1: Palm size (30)
//      2: Arm size (15)
//      3: Torse size (5)
//      4: Body (1)
//      5: Bigger (0)
const Item items[] = {                                            
    {"Chicken Egg", "Layed by a chicken, this fragile, oval object will produce a chiken if left alone long enough.", {elementaryItems[0], elementaryItems[1]}, 1, 1}, // 0
    {"Candle", "A cylinder of wax which can be lit to produce light and sometimes scents.", {elementaryItems[5], elementaryItems[6]}, 2, 1}, // 1
    {"Sheets", "Large rectangular piece of cloth.", {elementaryItems[8]}, 2, 2}, // 2
    {"Fork", "A four pronged metal eating device. Hold the end without the prongs.", {elementaryItems[2]}, 3, 1}, // 3
    {"Butter knife", "A not so sharp knife which can be used to cut butter (duh).", {elementaryItems[2]}, 3, 1}, // 4
    {"Plate", "A dish to separate the food and the table", {elementaryItems[9]}, 1, 2}, // 5
    {"Dart", "A small pointed missile which is (usually) thrown at a dart board in a friendly game.", {elementaryItems[2]}, 3, 1}, // 6
    {"Lute", "A plucked string instrament.", {elementaryItems[3], elementaryItems[10]}, 2, 3}, // 7
    {"Book", "Leather bound pieces of paper which tell a story or explain something.", {elementaryItems[11], elementaryItems[12]}, 2, 2}, // 8
    {"Metal Armor", "Several protective sheets of metal usually worn in battle.", {elementaryItems[2]}, 3, 4}, // 9
    {"Gold bar", "A brick of gold. What you would give for just one of them.", {elementaryItems[13]}, 3, 1}, // 10
    {"Painting", "A painted picture, Could be of literally anything. Some call it art, some, dont.", {elementaryItems[14], elementaryItems[8], elementaryItems[3]}, 2, 3}, // 11
    {"Pan", "An open container used to cook food.", {elementaryItems[15]}, 3, 2}, // 12
    {"Fancy painting", "Like a painting, but worth more.", {elementaryItems[14], elementaryItems[8], elementaryItems[3]}, 2, 3}, // 13
};

// std::string name;
// std::string description;
// int typeOfContainer;
//      0: No storage
//      1: In storage
//      3: On storage
//      4: Cold storage
//      5: Hot storage
// std::vector<Item> itemsContained;
const Furniture furniture[] = {
    {"Chair", "A seat for one person, usually has a back and four legs. Sadly does not walk.", 0}, // 0
    {"Bed", "A place for sleeping, often has a mattress, pillow, and blanket.", 0}, // 1
    {"King's bed", "A big fancy bed which talks up half the room.", 0}, // 2
    {"Shelf", "A rigid rectangle attached to a wall, used to store things.", 3}, // 3
    {"Table", "A big rectangle with four legs, usually eaten off of.", 3}, // 4
    {"Fireplace", "A place for controlled fire, hopfully at the base of a chimany", 5}, // 5
    {"Dartboard", "A board hung on a wall which darts are thrown at for points", 3}, // 6
    {"Coffee table", "A small table used to hold small items (like coffee).", 3}, // 7
    {"Oven", "An enclosed compartment used for heating food", 5}, // 8
    {"Desk", "A place were one can sit and do work. Or procrastinate.", 3}, // 9
    {"Training dummy", "A fake person (hopefully you knew that), used to practice fighting skills.", 0}, // 10
    {"Piano", "A large percussion instrument were tiny hammers hit strings of different length.", 0} // 11
};


// manditoryItem
// possibleItems
// manditoryFurniture
// possibleFurniture
const RoomFilling roomFilling[12] = {
    {}, // Unused
    {emptyItem, {items[1], items[11]}, furniture[2], {furniture[5]}}, // King's bedroom
    {items[12], {items[0]}, furniture[8], {furniture[4]}}, // kitchen
    {items[2], {items[1]}, furniture[3]}, // storeroom
    {items[5], {items[3], items[4]}, furniture[4], {furniture[5]}}, // dinning room
    {items[1], {}, furniture[1]}, // servants corridor
    {items[6], {}, furniture[6], {furniture[7]}}, // game room
    {items[7], {}, furniture[11]}, // music room
    {items[8], {}, furniture[9]}, // library
    {items[9], {}, furniture[10]}, // armory
    {items[10], {items[11]}, furniture[14]}, // treasure room
    {items[11], {}, furniture[7]} // hall
};



// Differnt room types and their corresponding numbers
// 0 is the defalt
RoomType roomTypes[12] = {
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