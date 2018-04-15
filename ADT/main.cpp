/*
 * main.cpp
 *
 *  Created on: 5 April 2018
 *      Author: user
 */
#include <iostream>
#include <cstring>
#include "RPSPiece.h"
#include "RPSCommand.h"
#include "RPSGame.h"
#include "MainAux.h"

#define PLAYER1_MOVES_FILE "player1.rps_moves"
#define PLAYER2_MOVES_FILE "player2.rps_moves"

int main() {
	RPSGame game = RPSGame();
	int winner = 0;
	std::string player1PositionFile = "player1.rps_board";
	std::string player2PositionFile = "player2.rps_board";
	int player1Positioning = MainAux::rpsLoadPositionFile(game, player1PositionFile, 1);
	int player2Positioning = MainAux::rpsLoadPositionFile(game, player2PositionFile, 2);
	if (player1Positioning == -1 && player2Positioning == -1) {
		std::cout << "ERROR: Could not open either positioning file. Quitting..." << std::endl;
		return 1;
	}
	else if (player1Positioning == -1) {
		std::cout << "ERROR: Could not open player 1's positioning file. Quitting..." << std::endl;
		return 1;
	}
	else if (player2Positioning == -1) {
		std::cout << "ERROR: Could not open player 2's positioning file. Quitting..." << std::endl;
		return 1;
	}


	if (player1Positioning > 0 || player2Positioning > 0) {
		return MainAux::rpsPrintGamePositionErrorResult(game,player1Positioning,player2Positioning);
	}

	std::string player1MovesFile = PLAYER1_MOVES_FILE;
	std::string player2MovesFile = PLAYER2_MOVES_FILE;

	int reason = MainAux::rpsPlayTwoPlayerMoves(game,player1MovesFile,player2MovesFile);

	return MainAux::rpsPrintGameResult(game,reason);

}
