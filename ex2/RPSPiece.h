#ifndef RPSPIECE_H_
#define RPSPIECE_H_

#include <iostream>
#define NONE '0'
#define NOT_JOKER '#'
//enum PieceType {None, Rock, Paper, Scissors, Bomb, Flag, InvalidPiece};

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

	char getPieceType() { return this->pieceType; }

	void setJokerRepresentation(char pieceType) { if (this->pieceType == 'J') this->jokerRepresentation = pieceType; }

	char getJokerRepresentation() { return this->jokerRepresentation; }

	int getPlayer() { return this->player; }
};

#endif

