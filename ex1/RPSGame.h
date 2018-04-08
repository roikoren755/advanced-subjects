/*
 * RPSGame.h
 *
 *  Created on: 8 ���� 2018
 *      Author: user
 */
#include "RPSPiece.h"
#include "RPSCommand.h"

#define N 10
#define M 10

enum RPS_Massage{Success,Invalid_Argument,Bad_Position,Index_Out_Of_Range};

class Game{
	Piece board[N][M];
	int currentPlayer;

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

	Piece RPSPerformBattle(Piece piece1,Piece piece2);

	void Game::RPSExcludePiece();
};