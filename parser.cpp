#include <string>
#include <iostream>
#include <cctype>

#include "KingServent.h"

using namespace std;

string getInput(){
    string rawInput;
    int command = 0;
    do {
        cin >> rawInput;
        for (int i = 0; i < rawInput.size(); i++){
            rawInput[i] = tolower(rawInput[i]);
        }
        for (int i = 0; i < (sizeof(commands)/sizeof(commands[0])); i++){
            for (int j = 0; j < (sizeof(commands[i])/sizeof(commands[i][0])); j++){
                if (rawInput == commands[i][j]){
                    command = i;
                }
            }
        }

    } while (command == 0);
    printf("%i\n", command);
}