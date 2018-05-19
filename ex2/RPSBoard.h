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
public:
	RPSPiece board[N_PLAYERS][N][M]; // TODO - fix meeee: can leave it like this, or change to functions of getting and setting
	int getPlayer(const Point& pos) const override;
	RPSPiece& getPiece(const Point& pos);
	RPSPiece& getPiece(int x,int y);
	~RPSBoard() override = default;
};

#endif //ADVANCED_SUBJECTS_RPSBOARD_H
