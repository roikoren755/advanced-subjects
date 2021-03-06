//
// Created by Roi Koren on 30/04/2018.
//

#ifndef ADVANCED_SUBJECTS_RPSMOVE_H
#define ADVANCED_SUBJECTS_RPSMOVE_H

#include "Move.h"
#include "Point.h"

class RPSMove: public Move {
	const RPSPoint from;
	const RPSPoint to;
public:
	RPSMove(int fromX, int fromY, int toX, int toY): from(RPSPoint(fromX, fromY)), to(RPSPoint(toX, toY)) {}
	RPSMove(const Point& from, const Point& to): from(from), to(to) {}
	RPSMove(const Move& move): from(move.getFrom()), to(move.getTo()) {}
	const Point& getFrom() const override { return this->from; }
	const Point& getTo() const override { return this->to; }
	~RPSMove() override = default;
};

#endif //ADVANCED_SUBJECTS_RPSMOVE_H
