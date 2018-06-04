//
// Created by Roi Koren on 30/04/2018.
//

#ifndef ADVANCED_SUBJECTS_RPSPIECEPOSITION_H
#define ADVANCED_SUBJECTS_RPSPIECEPOSITION_H

#include "PiecePosition.h"
#include "RPSPoint.h"

#define INVALID_PIECE '#'

class RPSPiecePosition: public PiecePosition {
	const RPSPoint position;
	const char piece;
	const char jokerRepresentation;
public:
	RPSPiecePosition(int x, int y, char piece, char jokerRepresentation): position(RPSPoint(x, y)), piece(piece),
																		  jokerRepresentation(jokerRepresentation) {}
	RPSPiecePosition(const Point& position, char piece, char jokerRepresentation): position(position), piece(piece),
																			jokerRepresentation(jokerRepresentation) {}
	RPSPiecePosition(const PiecePosition& piecePosition): position(piecePosition.getPosition()),
												   piece(piecePosition.getPiece()),
												   jokerRepresentation(piecePosition.getJokerRep()) {}
	RPSPiecePosition(const PiecePosition&& piecePosition): position(piecePosition.getPosition()), piece(piecePosition.getPiece()),
														jokerRepresentation(piecePosition.getJokerRep()) {}
	const Point& getPosition() const override { return this->position; }
	char getPiece() const override { return this->piece; }
	char getJokerRep() const override { return this->jokerRepresentation; }
	~RPSPiecePosition() override = default;
};

#endif //ADVANCED_SUBJECTS_RPSPIECEPOSITION_H
