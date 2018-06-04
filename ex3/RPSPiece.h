#ifndef RPSPIECE_H_
#define RPSPIECE_H_

#include <iostream>
#define NONE '0'
#define NOT_JOKER '#'


class RPSPiece {
	char pieceType;
	char jokerRepresentation;
	int player;
public:
	//empty constructor for null piece
	RPSPiece(): pieceType(NONE), jokerRepresentation(NONE), player(0) {}
	//constructor with parameters for Non-Joker
    RPSPiece(char pieceType, int player): pieceType(pieceType),jokerRepresentation(NOT_JOKER), player(player) {}
    RPSPiece(char pieceType, char jokerRepresentation, int player): pieceType(pieceType),
																	jokerRepresentation(jokerRepresentation),
																	player(player) {}
	RPSPiece& operator=(const RPSPiece&);
	friend std::ostream& operator<<(std::ostream &out, RPSPiece &piece);
	//getters and setters:
	char getPieceType() const { return this->pieceType; }
	void setJokerRepresentation(char pieceType) { if (this->pieceType == 'J') this->jokerRepresentation = pieceType; }
	char getJokerRepresentation() { return this->jokerRepresentation; }
	int getPlayer() { return this->player; }
};

#endif
