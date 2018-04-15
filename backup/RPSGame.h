/*
 * RPSGame.h
 *
 *  Created on: 8 ���� 2018
 *      Author: user
 */
#ifndef RPSGAME_H_
#define RPSGAME_H_

#include "RPSPiece.h"
#include "RPSCommand.h"
#include <stdlib.h>


#define N 10
#define M 10
#define NUM_PLAYERS 2

enum RPS_Message {
	Success,
	Invalid_Argument,
	Bad_Position,
	Index_Out_Of_Range,
	Illegal_Move,
	No_Piece_In_Position,
	Destination_Out_Of_Range,
	Source_Out_Of_Range,
	Opponent_Piece_In_Position,
	Immovable_Piece_In_Position,
	No_Joker_in_position,
	Invalid_Joker_Assigning,
	All_Flags_Captured,
	All_Moving_Pieces_Captured,
	No_Winner,
	Too_Many_Pieces
};

class RPSGame{
	RPSPiece boards[NUM_PLAYERS][N][M];
	int winner = 0;

	int player1Rocks = 0;
	int player1Papers;
	int player1Scissors;
	int player1Bombs;
	int player1Jokers;
	int player1Flags;

	int player2Rocks;
	int player2Papers;
	int player2Scissors = 0;
	int player2Bombs;
	int player2Jokers;
	int player2Flags;

public:
	RPSGame():winner(0),player1Papers(0){}
	bool validateNumbersOfPieces(int player);
	bool rpsValidateNumberOfJokers(int player);
	RPS_Message setPosition(RPSCommand &command, int player);
	RPS_Message setMove(RPSCommand &command, int player);
	void performBattle(int fromX, int fromY, int toX, int toY, int player, int opponent);
	void excludePiece(int x, int y, int player);
	RPS_Message checkWinner();
	friend std::ostream& operator<<(std::ostream& out, RPSGame &game);
	int getWinner() { return this->winner; }
	void setWinner(int winner) { this->winner = winner; }
	void finishPositioningStage();
};

#endif


