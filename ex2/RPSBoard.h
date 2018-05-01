//
// Created by Roi Koren on 30/04/2018.
//

#ifndef ADVANCED_SUBJECTS_RPSBOARD_H
#define ADVANCED_SUBJECTS_RPSBOARD_H

#include "Board.h"
#include "Point.h"

#define N 10
#define M 10

#define N_PLAYERS 2

class RPSBoard: public Board {
	char board[N_PLAYERS][N][M];
public:
	int getPlayer(const Point& pos) const override;
	~RPSBoard() {}
};

#endif //ADVANCED_SUBJECTS_RPSBOARD_H
