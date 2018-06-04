//
// Created by user on 01/05/2018.
//
#include <iostream>
#include <algorithm>
#include "MainAux.h"
#include "RPSGame.h"

int main() {
    std::vector<unique_ptr<PlayerAlgorithm>> algorithms;// =  std::vector<unique_ptr<PlayerAlgorithm>>(2);;

    RPSGame game = RPSGame();
    int feedback = MainAux::RPSPerformPositioning(game,algorithms);
    if(feedback>0){
        return MainAux::RPSPrintGamePositionErrorResult(game, feedback);
    }

    std::vector<unique_ptr<FightInfo>> fights;

    int reason = game.finishPositioningStage(fights);
    if (reason) { // game is done
        return MainAux::RPSPrintGameResult(game, reason);
    }

    algorithms[PLAYER(1)]->notifyOnInitialBoard(game.getBoard(),fights);
    algorithms[PLAYER(2)]->notifyOnInitialBoard(game.getBoard(),fights);

    reason = MainAux::RPSPlayTwoPlayersMoves(game, algorithms);

    return MainAux::RPSPrintGameResult(game, reason);
}

