//
// Created by Roi Koren on 09/04/2018.
//

#ifndef ADVANCED_SUBJECTS_MAINAUX_H
#define ADVANCED_SUBJECTS_MAINAUX_H

#include "RPSGame.h"

class MainAux {
	static int rpsLoadPositionFile(RPSGame &rpsGame, std::string &positionFile, int player);
	static int rpsPlayTwoPlayerMoves(RPSGame &rpsGame, std::string &player1MoveFile, std::string &player2MoveFile);
};

#endif //ADVANCED_SUBJECTS_MAINAUX_H
