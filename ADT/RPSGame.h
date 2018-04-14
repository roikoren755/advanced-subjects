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
	RPSGame();
	bool rpsValidateNumbersOfPieces(int player);
	bool rpsValidateNumberOfJokers(int player);
	RPS_Message rpsSetPosition(RPSCommand &command, int player);
	RPS_Message rpsSetMove(RPSCommand &command, int player);
	RPSPiece& rpsPerformBattle(int fromX, int fromY, int toX, int toY, int player, int opponent);
	void rpsExcludePiece(int x, int y, int player);
	RPS_Message rpsCheckWinner();
	friend ostream& operator<<(ostream& out, RPSGame &game);
	int rpsGetWinner() { return this->winner; }
	void rpsSetWinner(int winner) { this->winner = winner; }
	void rpsFinishPositioningStage();
};



