//
// Created by Roi Koren on 16/06/2018.
//
#include "RPSMove.h"

RPSMove& RPSMove::operator=(const RPSMove &other) {
	if (this == &other) {
		return *this;
	}
	this->from = other.from;
	this->to = other.to;
	return *this;
}
