/*
 * RPSCommand.h
 *
 *  Created on: 5 April 2018
 *      Author: user
 */

#ifndef RPSCOMMAND_H_
#define RPSCOMMAND_H_

#include "RPSPiece.h"

#define MAXIMUM_COMMAND_LENGTH 1024

enum CommandType {Position, Move, InvalidCommand};

class RPSCommand {
	CommandType commandType;
	PieceType pieceType;
	int fromX;
	int fromY;
	int toX;
	int toY;
	bool jokerInvolved;
	int jokerX;
	int jokerY;

public:
	RPSCommand(CommandType commandType, PieceType pieceType, int fromX, int fromY, int toX, int toY, bool jokerInvolved,
			   int jokerX, int jokerY): commandType(commandType), pieceType(pieceType), fromX(fromX),
										fromY(fromY), toX(toX), toY(toY), jokerInvolved(jokerInvolved), jokerX(jokerX),
										jokerY(jokerY) {};
	CommandType getCommandType() { return this->commandType; };
	PieceType getPieceType() { return this->pieceType; };
	int getfromX() { return this->fromX; };
	int getfromY() { return this->fromY; };
	int getToX() { return this->toX; };
	int getToY() { return this->toY; };
	bool isJokerInvolved() { return this->jokerInvolved; };
	int getJokerX() { return this->jokerX; };
	int getJokerY() { return this->jokerY; };
};

#endif /* RPSCOMMAND_H_ */
© 2018 GitHub, Inc.
Terms
		Privacy
Security
		Status
Help
		Contact GitHub
		API
Training
		Shop
Blog
		About
Press h to open a hovercard with more details.