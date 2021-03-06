/*
 * RPSGame.h
 *
 *  Created on: 8 April 2018
 *      Author: user
 */
#ifndef RPSGAME_H_
#define RPSGAME_H_

#include "RPSPiece.h"
#include "PlayerAlgorithm.h"
#include "RPSBoard.h"
#include "Move.h"
#include "RPSPiecePosition.h"
#include "RPSFightInfo.h"


#define N 10
#define M 10
#define NUM_PLAYERS 2


/**
 * represent a game, contains data:
 * - 2 NxM game boards, 1 for each player(2 are needed for initialization stage.
 *   if there is a spot with a piece in both boards we notify an error)
 * - the winner
 * - The amounts of pieces of any type for both users
*/


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

class RPSGame {
	RPSBoard board;
	int winner = 0;

	int player1Rocks = 0;
	int player1Papers = 0;
	int player1Scissors = 0;
	int player1Bombs = 0;
	int player1Jokers = 0;
	int player1Flags = 0;

	int player2Rocks = 0;
	int player2Papers = 0;
	int player2Scissors = 0;
	int player2Bombs = 0;
	int player2Jokers = 0;
	int player2Flags = 0;

public:
	RPSGame() = default;

	// checks if the number of pieces of one player did not exceeded
	bool validateNumbersOfPieces(int player);

	// checks if the number of flags for one player is as it should be when initialized
	bool validateNumberOfFlags(int player);

    RPS_Message setInitialPositions(std::vector<unique_ptr<PiecePosition>>& positions, int player);

	// sets a position in the game, given a command and the player.
	// returns An appropriate message with the information -
	// whether there was an error and if so what it is
	RPS_Message setPosition(PiecePosition& position, int player);

	// sets a Move in the game, given a command and the player
	RPS_Message setMove(unique_ptr<Move> move, int player);

	// performs a battle between 2 pieces and sets the winner(if there is) at his spot
	RPSFightInfo performBattle(int x, int y);

	// removes a piece from the board and subtract the counter for that piece by 1
	void excludePiece(int x, int y, int player);

	// checks the winner, if game is over returns a message with the reason
	RPS_Message checkWinner();

	// after all pieces are set performs battles between every 2 pieces at the same spot,
	// returns 0 if the game isn't over, or an int representing a massage for the reason why the
	// game is over
	int finishPositioningStage(std::vector<std::unique_ptr<FightInfo>>& vectorToFill);

	friend std::ostream& operator<<(std::ostream& out, RPSGame &game);

	// getters and setters
	int getWinner() { return this->winner; }
	void setWinner(int winner) { this->winner = winner; }
};

#endif


