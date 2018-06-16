//
// Created by Roi Koren on 30/04/2018.
//
#ifndef ADVANCED_SUBJECTS_RPSMOVE_H
#define ADVANCED_SUBJECTS_RPSMOVE_H

#include "Move.h"
#include "RPSPoint.h"

class RPSMove: public Move {
	 RPSPoint from;
	 RPSPoint to;
public:
	RPSMove(int fromX, int fromY, int toX, int toY): from(RPSPoint(fromX, fromY)), to(RPSPoint(toX, toY)) {}
	RPSMove(const Point& from, const Point& to): from(from), to(to) {}
	RPSMove(const Move& move): from(move.getFrom()), to(move.getTo()) {}
<<<<<<< HEAD
	RPSMove& operator=(const RPSMove& other){
		if(this == &other){
			return *this;
		}
		this->from = other.from;
		this->to = other.to;
		return *this;
	}
	RPSMove(const Move&& move): from(move.getFrom()), to(move.getTo()) {}
=======
	RPSMove(const Move&& move): from(move.getFrom()), to(move.getTo()) {}
	RPSMove& operator=(const RPSMove& other);
>>>>>>> 130bc3c5cd744fc710557c3a80db9ef81f36ffc7
	const Point& getFrom() const override { return this->from; }
	const Point& getTo() const override { return this->to; }

	~RPSMove() override = default;
};

#endif //ADVANCED_SUBJECTS_RPSMOVE_H
