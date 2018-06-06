//
// Created by Roi Koren on 30/04/2018.
//
#ifndef ADVANCED_SUBJECTS_RPSJOKERCHANGE_H
#define ADVANCED_SUBJECTS_RPSJOKERCHANGE_H

#include "JokerChange.h"
#include "RPSPoint.h"

class RPSJokerChange: public JokerChange {
	const RPSPoint position;
	const char newRepresentation;
public:
	RPSJokerChange(int x, int y, char newRepresentation): position(RPSPoint(x, y)), newRepresentation(newRepresentation) {}
	RPSJokerChange(const Point& position, char newRepresentation): position(position), newRepresentation(newRepresentation) {}
	RPSJokerChange(JokerChange&& jokerChange): position(jokerChange.getJokerChangePosition()),
											  newRepresentation(jokerChange.getJokerNewRep()) {}
	RPSJokerChange(const JokerChange& jokerChange): position(jokerChange.getJokerChangePosition()),
											  newRepresentation(jokerChange.getJokerNewRep()) {}
	const Point& getJokerChangePosition() const override { return this->position; }
	char getJokerNewRep() const override { return this->newRepresentation; }
	~RPSJokerChange() override = default;
};

#endif //ADVANCED_SUBJECTS_RPSJOKERCHANGE_H
