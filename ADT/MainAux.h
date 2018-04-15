//
// Created by Roi Koren on 09/04/2018.
//

#ifndef ADVANCED_SUBJECTS_MAINAUX_H
#define ADVANCED_SUBJECTS_MAINAUX_H

#include "RPSGame.h"
#define ALL_FLAGS_CAPTURED -2
#define ALL_MOVING_PIECES_CAPTURED -3
#define LEGAL_TIE 0

class MainAux {
public:
	static int rpsPrintGamePositionErrorResult(RPSGame &rpsGame,int player1lineError,int player2lineError);
	static int rpsPrintGameResult(RPSGame &game,int reason);
	static int rpsLoadPositionFile(RPSGame &rpsGame, std::string &positionFile, int player);
	static int rpsPlayTwoPlayerMoves(RPSGame &rpsGame, std::string &player1MoveFile, std::string &player2MoveFile);
};

#endif //ADVANCED_SUBJECTS_MAINAUX_H
