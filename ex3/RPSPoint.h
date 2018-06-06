//
// Created by Roi Koren on 30/04/2018.
//
#ifndef ADVANCED_SUBJECTS_RPSPOINT_H
#define ADVANCED_SUBJECTS_RPSPOINT_H

#include "Point.h"

class RPSPoint : public Point {
	 int x;
	 int y;
public:
	RPSPoint(): x(-1),y(-1) {}
	RPSPoint(int x, int y): x(x), y(y) {}
	explicit RPSPoint(const Point&& point): x(point.getX()), y(point.getY()) {}
	explicit RPSPoint(const Point& point): x(point.getX()), y(point.getY()) {}
	int getX() const override { return this->x; }
	int getY() const override { return this->y; }
	void setX(int x)   { this->x = x; }
	void setY(int y)   { this->y = y; }

	~RPSPoint() override = default;
};

#endif //ADVANCED_SUBJECTS_RPSPOINT_H
