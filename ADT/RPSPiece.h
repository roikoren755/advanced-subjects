#ifndef RPSPIECE_H_
#define RPSPIECE_H_

#include <iostream>

enum PieceType {None, Rock, Paper, Scissors, Bomb, Flag, InvalidPiece};

class RPSPiece {
	PieceType pieceType;
	const bool isJoker;
	int player;
public:
	RPSPiece(): pieceType(None), isJoker(false), player(0) {}
	RPSPiece(PieceType pieceType, bool isJoker, int player): pieceType(pieceType), isJoker(isJoker), player(player) {}
	friend std::ostream& operator<<(std::ostream &out, RPSPiece &piece);
	PieceType getPieceType() { return this->pieceType; }
	void setPieceType(PieceType pieceType) { if (this->isPieceJoker()) this->pieceType = pieceType; }
	bool isPieceJoker() { return this->isJoker; }
	int getPlayer() { return this->player; }
};

#endif
