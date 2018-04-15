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
#define PLAYER1_POSITION_FILE "player1.rps_board"
#define PLAYER2_POSITION_FILE "player2.rps_board"
#define PLAYER1_MOVES_FILE "player1.rps_moves"
#define PLAYER2_MOVES_FILE "player2.rps_moves"

int main() {
	RPSGame game = RPSGame();

	std::string player1PositionFile = PLAYER1_POSITION_FILE;
	std::string player2PositionFile = PLAYER2_POSITION_FILE;
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
		MainAux::rpsPrintGamePositionErrorResult(game,player1Positioning,player2Positioning);
	}
	else{
		int reason = game.rpsFinishPositioningStage();
		if (reason) {  //game is done
				 MainAux::rpsPrintGameResult(game,reason);
		}
		else{
			std::string player1MovesFile = PLAYER1_MOVES_FILE;
				std::string player2MovesFile = PLAYER2_MOVES_FILE;

				reason = MainAux::rpsPlayTwoPlayerMoves(game,player1MovesFile,player2MovesFile);

				 MainAux::rpsPrintGameResult(game,reason);
		}
	}

	delete &game;


}
