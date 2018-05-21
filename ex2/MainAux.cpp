//
// Created by user on 21/05/2018.
//
#include <string.h>
#include "PlayerAlgorithm.h"
#include "MainAux.h"
#include "RPSGame.h"


#define AUTO "auto"
#define FILE "file"
#define TOKENS "-vs"


RPSMakePlayerAlgorithm(int player, char arg[],std::vector<unique_ptr<PlayerAlgorithm>>& algorithms){
    char* players[NUM_PLAYERS];
    players[0] = strtok(arg,TOKENS);
    players[1] = strtok(NULL,TOKENS);
    int i = 0;
    for(int i = 0; i<NUM_PLAYERS; i++){
        if(strcpy(players[0],AUTO)){
            unique_ptr<PlayerAlgorithm> ptr = make_unique<PlayerAlgorithm>();
            *ptr =
            algorithms.insert(ptr);
        }
        else if(strcpy(players[0],AUTO)){
            unique_ptr<PlayerAlgorithm> ptr = make_unique<PlayerAlgorithm>();
            algorithms.insert(ptr);)
    }
}
