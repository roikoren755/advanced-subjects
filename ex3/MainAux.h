//
// Created by user on 21/05/2018.
//

#ifndef ADVANCED_SUBJECTS_MAINAUX_H
#define ADVANCED_SUBJECTS_MAINAUX_H

#include "RPSGame.h"

class MainAux {
public:
	static int runGame(unique_ptr<PlayerAlgorithm> player1, unique_ptr<PlayerAlgorithm> player2);
	static int GetPositiveInt(const char *const integer);
    static int RPSPerformPositioning(RPSGame& game ,std::vector<unique_ptr<PlayerAlgorithm>>& algorithms);
    static int RPSPrintGamePositionErrorResult(RPSGame& game, int feedback);
    static int RPSPlayTwoPlayersMoves(RPSGame& game, std::vector<unique_ptr<PlayerAlgorithm>>& algorithms);
    static int RPSPrintGameResult(RPSGame& game, int reason);
};

#endif //ADVANCED_SUBJECTS_MAINAUX_H
