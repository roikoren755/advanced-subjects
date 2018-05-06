#ifndef RPSPIECE_H_
#define RPSPIECE_H_

#include <iostream>
#define NONE '0'
enum PieceType {None, Rock, Paper, Scissors, Bomb, Flag, InvalidPiece};

/**
 * represent a piece, contains data:
 * - The piece type
 * - Is the piece a joker
 * - The player the piece belong to
*/


class RPSPiece {
	char pieceType;
	char jokerRepresentation;
	int player;
public:
	//empty constructor for null piece
	RPSPiece(): pieceType(NONE), jokerRepresentation(NONE), player(0) {}

	//constructor with parameters
	RPSPiece(char pieceType, char jokerRepresentation, int player): pieceType(pieceType),
												jokerRepresentation(jokerRepresentation), player(player) {}

	RPSPiece& operator=( const RPSPiece& );

	friend std::ostream& operator<<(std::ostream &out, RPSPiece &piece);

	//getters and setters:

	PieceType getPieceType() { return this->pieceType; }

	void setPieceType(PieceType pieceType) { if (this->isPieceJoker()) this->pieceType = pieceType; }

	bool isPieceJoker() { return this->isJoker; }

	int getPlayer() { return this->player; }
};

#endif

