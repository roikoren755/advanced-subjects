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

	std::cout<<player1Positioning<<player2Positioning<<std::endl;


	if (player1Positioning > 0 || player2Positioning > 0) {
		return MainAux::rpsPrintGamePositionErrorResult(game,player1Positioning,player2Positioning);
	}

	if (!winner) {

	}

	std::cout<<game<<std::endl;
}
