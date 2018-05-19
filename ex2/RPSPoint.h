//
// Created by Roi Koren on 30/04/2018.
//

#ifndef ADVANCED_SUBJECTS_RPSPOINT_H
#define ADVANCED_SUBJECTS_RPSPOINT_H

#include "Point.h"

class RPSPoint : public Point {
	const int x;
	const int y;
public:
	RPSPoint(int x, int y): x(x), y(y) {}
	RPSPoint(const Point&& point): x(point.getX()), y(point.getY()) {}
	RPSPoint(const Point& point): x(point.getX()), y(point.getY()) {}
	int getX() const override { return this->x; }
	int getY() const override { return this->y; }
	~RPSPoint() override = default;
};

#endif //ADVANCED_SUBJECTS_RPSPOINT_H
