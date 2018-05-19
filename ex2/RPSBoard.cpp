// Created by Roi Koren on 30/04/2018.
//

#include "RPSBoard.h"

int RPSBoard::getPlayer(const Point &pos) const {
	int x = pos.getX();
	int y = pos.getY();

	if (this->board[0][y - 1][x - 1].getPieceType() != NONE) return 1;
	if (this->board[0][y - 1][x - 1].getPieceType() != NONE) return 2;

	return 0;
}
RPSPiece& RPSBoard::getPiece(int x, int y) {
	if (this->board[0][y - 1][x - 1].getPieceType() != NONE) {
		return this->board[0][y - 1][x - 1];
	}

	return this->board[1][y - 1][x - 1];
}

RPSPiece& RPSBoard::getPiece(const Point& pos) {
	int x = pos.getX();
	int y = pos.getY();

	return this->getPiece(x,y);
}

