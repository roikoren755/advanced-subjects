/*
 * main.cpp
 *
 *  Created on: 5 באפר 2018
 *      Author: user
 */
#include <iostream>
#include <cstring>
#include "RPSPiece.h"
#include "RPSCommand.h"
#include "RPSGame.h"
#include "MainAux.h"

int main(int argc, char* argv[]) {
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

	if (player1Positioning == -2 && player2Positioning == -2) {
		std::cout << "ERROR: Neither player placed all of his flags. Quitting..." << std::endl;
		winner = -1;
	}
	else if (player1Positioning == -2) {
		std::cout << "ERROR: Player 1 hadn't placed all of his flags. Quitting..." << std::endl;
		winner = 2;
	}
	else if (player2Positioning == -2) {
		std::cout << "ERROR: Player 2 hadn't placed all of his flags. Quitting..." << std::endl;
		winner = 1;
	}

	if (player1Positioning > 0 && player2Positioning > 0) {
		winner = -1;
	}

	if (!winner) {

	}
}

