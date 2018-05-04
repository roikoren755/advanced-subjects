

// Created by Roi Koren on 30/04/2018.
//

#include "RPSBoard.h"

int RPSBoard::getPlayer(const Point &pos) const {
	int x = pos.getX();
	int y = pos.getY();

	if (this->board[0][y - 1][x - 1].getPieceType() != None) return 1;
	if (this->board[0][y - 1][x - 1].getPieceType() != None) return 2;

	return 0;
}

RPSPiece RPSBoard::getPiece(const Point& pos){
    if (this->board[0][y - 1][x - 1].getPieceType() != None) return this->board[0][y - 1][x - 1];
    if (this->board[0][y - 1][x - 1].getPieceType() != None) return this->board[0][y - 1][x - 1];

    return &this->board[0][y - 1][x - 1];
}

