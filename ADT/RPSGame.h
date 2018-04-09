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

enum RPS_Message{Success,
				Invalid_Argument,
				Bad_Position,
				Index_Out_Of_Range,
				Illegal_Move,
				No_Piece_In_Position,
				Destinations_Out_Of_Range,
				Source_Out_Of_Range,
				Opponent_Piece_In_Position,
				Immovable_Piece_In_Position,
				No_Joker_in_position,
				Invalid_Joker_Assigning,
				All_Flags_Captured,
				All_Moving_Pieces_Captured,
				No_Winner
};

class Game{
	Piece board[N][M];
	//int currentPlayer;
	int winner;

	int player1Rocks;
	int player1Papers;
	int player1Scissors;
	int player1Bombs;
	int player1Jokers;
	int player1Flags;

	int player2Rocks;
	int player2Papers;
	int player2Scissors;
	int player2Bombs;
	int player2Jokers;
	int player2Flags;

public:

	RPS_Message RPSSetPosition(RPSCommand command,int player);

	RPS_Message RPSSetMove(RPSCommand command, int player);

	Piece RPSPerformBattle(Piece piece1,Piece piece2);

	void RPSExcludePiece(Piece piece);

	RPS_Message RPSCheckWinner();

	friend ostream& operator<<(ostream& out,Game game);

};



