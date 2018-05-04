//
// Created by Roi Koren on 30/04/2018.
//

#ifndef ADVANCED_SUBJECTS_RPSBOARD_H
#define ADVANCED_SUBJECTS_RPSBOARD_H

#include "Board.h"
#include "Point.h"
#include "RPSPiece.h"

#define N 10
#define M 10

#define N_PLAYERS 2

class RPSBoard: public Board {
	RPSPiece board[N_PLAYERS][N][M];
public:
	int getPlayer(const Point& pos) const override;
	RPSPiece getPiece(const Point& pos);
	~RPSBoard() {}
};

#endif //ADVANCED_SUBJECTS_RPSBOARD_H
