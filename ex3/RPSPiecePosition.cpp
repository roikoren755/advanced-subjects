//
// Created by Roi Koren on 07/06/2018.
//
#include "RPSPiecePosition.h"

RPSPiecePosition& RPSPiecePosition::operator=(const RPSPiecePosition &other) {
	if (this == &other) {
		return *this;
	}

	this->position.setX(other.getPosition().getX());
	this->position.setY(other.getPosition().getY());
	this->piece = other.getPiece();
	this->jokerRepresentation = other.getJokerRep();

	return *this;
}