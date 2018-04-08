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

#define N 10
#define M 10

enum RPS_Massage{Success,Invalid_Argument,Bad_Position,Index_Out_Of_Range};

class Game{
	Piece board[N][M];
	Player currentPlayer;

	int player1rocks;
	int player1Papers;
	int player1Scissors;
	int player1Bombs;
	int player1Jokers;
	int player1Flags;

	int player2rocks;
	int player2Papers;
	int player2Scissors;
	int player2Bombs;
	int player2Jokers;
	int player2Flags;

public:
	RPS_Massage RPSSetPosition(Command command,int player);

	RPS_Massage RPSSetMove(Command command);
};



#endif /* RPSGAME_H_ */
