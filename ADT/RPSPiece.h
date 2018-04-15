#ifndef RPSPIECE_H_
#define RPSPIECE_H_

#include <iostream>

enum PieceType {None, Rock, Paper, Scissors, Bomb, Flag, InvalidPiece};

/**
 * represent a piece, contains data:
 * - The piece type
 * - Is the piece a joker
 * - The player the piece belong to
*/


class RPSPiece {
	PieceType pieceType;
	bool isJoker;
	int player;
public:
	//empty constructor for null piece
	RPSPiece(): pieceType(None), isJoker(false), player(0) {}

	//constructor with parameters
	RPSPiece(PieceType pieceType, bool isJoker, int player): pieceType(pieceType), isJoker(isJoker), player(player) {}

	RPSPiece& operator=( const RPSPiece& );

	friend std::ostream& operator<<(std::ostream &out, RPSPiece &piece);

	//getters and setters:

	PieceType getPieceType() { return this->pieceType; }

	void setPieceType(PieceType pieceType) { if (this->isPieceJoker()) this->pieceType = pieceType; }

	bool isPieceJoker() { return this->isJoker; }

	int getPlayer() { return this->player; }
};

#endif

