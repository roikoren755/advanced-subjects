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
	//prints the position in the file when an error in the position file occurred
	static int rpsPrintGamePositionErrorResult(RPSGame &rpsGame,int player1lineError,int player2lineError);

	//prints the position in the file when a different error occurred
	static int rpsPrintGameResult(RPSGame &game,int reason);

	//loads a position file into a game and returns the status
	static int rpsLoadPositionFile(RPSGame &rpsGame, std::string &positionFile, int player);

	//loads the moves files into a game and returns the status
	static int rpsPlayTwoPlayerMoves(RPSGame &rpsGame, std::string &player1MoveFile, std::string &player2MoveFile);
};

#endif //ADVANCED_SUBJECTS_MAINAUX_H
