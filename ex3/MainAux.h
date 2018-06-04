//
// Created by user on 21/05/2018.
//

#ifndef ADVANCED_SUBJECTS_MAINAUX_H
#define ADVANCED_SUBJECTS_MAINAUX_H

#include "RPSGame.h"

#define SUCCESS 0
#define PLAYER(i) ((i) - 1)


class MainAux {
public:
    static int RPSMakePlayerAlgorithm(int argc, char arg[], std::vector<unique_ptr<PlayerAlgorithm>>& algorithms);
    static int RPSPerformPositioning(RPSGame& game ,std::vector<unique_ptr<PlayerAlgorithm>>& algorithms);
    static int RPSPrintGamePositionErrorResult(RPSGame& game, int feedback);
    static int RPSPlayTwoPlayersMoves(RPSGame& game, std::vector<unique_ptr<PlayerAlgorithm>>& algorithms);
    static int RPSPrintGameResult(RPSGame& game, int reason);
};


#endif //ADVANCED_SUBJECTS_MAINAUX_H
