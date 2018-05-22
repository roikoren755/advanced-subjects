// Created by Roi Koren on 30/04/2018.
//

#include "RPSBoard.h"

RPSBoard::RPSBoard() {
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < 2; k++) {
				this->board[k][j][i] = RPSPiece();
			}
		}
	}
}

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

RPSPiece& RPSBoard::getPiece(int player, int x, int y) {
	return this->board[player - 1][y - 1][x - 1];
}

void RPSBoard::setPiece(int player, RPSPiece piece, int x, int y) {
	if (player != 1 && player != 2) {
		return;
	}

	if (x < 0 || x > M || y < 0 || y > N) {
		return;
	}

	this->board[player - 1][y - 1][x - 1] = piece;
}