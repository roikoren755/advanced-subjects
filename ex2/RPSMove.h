//
// Created by Roi Koren on 30/04/2018.
//

#ifndef ADVANCED_SUBJECTS_RPSMOVE_H
#define ADVANCED_SUBJECTS_RPSMOVE_H

#include "Move.h"
#include "Point.h"

class RPSMove: public Move {
	const Point from;
	const Point to;
	RPSMove(Point from, Point to): from(from), to(to) {}
	RPSMove(Move move): from(move.getFrom()), to(move.getTo()) {}
	RPSMove(Move& move): from(move.getFrom()), to(move.getTo()) {}
	const Point& getFrom() const override { return this->from; }
	const Point& getTo() const override { return this->to; }
	~RPSMove() override {}
};

#endif //ADVANCED_SUBJECTS_RPSMOVE_H
