//
// Created by Roi Koren on 30/04/2018.
//

#include "RPSBoard.h"

int RPSBoard::getPlayer(const Point &pos) const {
	int x = pos.getX();
	int y = pos.getY();

	if (this->board[0][y - 1][x - 1]) return 1;
	if (this->board[1][y - 1][x - 1]) return 2;

	return 0;
}