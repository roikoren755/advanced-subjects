//
// Created by Roi Koren on 30/04/2018.
//

#ifndef ADVANCED_SUBJECTS_RPSJOKERCHANGE_H
#define ADVANCED_SUBJECTS_RPSJOKERCHANGE_H

#include "JokerChange.h"
#include "Point.h"

class RPSJokerChange: public JokerChange {
	const Point position;
	const char newRepresentation;
public:
	RPSJokerChange(Point position, char newRepresentation): position(position), newRepresentation(newRepresentation) {}
	RPSJokerChange(JokerChange jokerChange): position(jokerChange.getJokerChangePosition()),
											 newRepresentation(jokerChange.getJokerNewRep()) {}
	RPSJokerChange(JokerChange& jokerChange): position(jokerChange.getJokerChangePosition()),
											  newRepresentation(jokerChange.getJokerNewRep()) {}
	const Point& getJokerChangePosition() const override { return &this->position; }
	char getJokerNewRep() const override { return this->newRepresentation; }
	~RPSJokerChange() override {}
};

#endif //ADVANCED_SUBJECTS_RPSJOKERCHANGE_H
