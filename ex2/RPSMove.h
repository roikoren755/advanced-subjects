//
// Created by Roi Koren on 30/04/2018.
//

#ifndef ADVANCED_SUBJECTS_RPSMOVE_H
#define ADVANCED_SUBJECTS_RPSMOVE_H

#include "Move.h"
#include "Point.h"

class RPSMove: public Move {
<<<<<<< HEAD
	const Point from;
	const Point to;
	RPSMove(Point from, Point to): from(from), to(to) {}
	RPSMove(Move move): from(move.getFrom()), to(move.getTo()) {}
	RPSMove(Move& move): from(move.getFrom()), to(move.getTo()) {}
	const Point& getFrom() const override { return this->from; }
	const Point& getTo() const override { return this->to; }
	~RPSMove() override {}
=======
	const RPSPoint from;
	const RPSPoint to;
public:
	RPSMove(int fromX, int fromY, int toX, int toY): from(RPSPoint(fromX, fromY)), to(RPSPoint(toX, toY)) {}
	RPSMove(const Point& from, const Point& to): from(from), to(to) {}
	RPSMove(const Move& move): from(move.getFrom()), to(move.getTo()) {}
	const Point& getFrom() const override { return this->from; }
	const Point& getTo() const override { return this->to; }
	~RPSMove() override = default;
>>>>>>> e515910ba0b086ad99de6b14be188d0fc58f39d3
};

#endif //ADVANCED_SUBJECTS_RPSMOVE_H
