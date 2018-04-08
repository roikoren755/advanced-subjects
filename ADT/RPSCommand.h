/*
 * RPSCommand.h
 *
 *  Created on: 5 באפר 2018
 *      Author: user
 */

#ifndef RPSCOMMAND_H_
#define RPSCOMMAND_H_

#include "RPSPiece.h"

enum CommandType{Position,Move};

class Command{
public:

	CommandType type;
	bool JokerInvolved;

	int toX;
	int toY;

	int FromX;
	int FromY;

	PieceType pieceType;
	int player;

	int jokerX;
	int jokerY;

public:
	CommandType getType();
	int getPlayer();
	PieceType getPieceType();
	int getfromX();
	int getfromY();
	int getToX();
	int getToY();
	int getJokerX();
	int getJokerY();
	bool isJokerInvolved();
};



#endif /* RPSCOMMAND_H_ */
