/*
 * RPSCommand.h
 *
 *  Created on: 5 ���� 2018
 *      Author: user
 */

#ifndef RPSCOMMAND_H_
#define RPSCOMMAND_H_

#include "RPSPiece.h"

#define MAXIMUM_COMMAND_LENGTH 1024

enum CommandType {Position, Move, InvalidCommand, NoLine};



/**
 * data structure for command, with all the necessary information
*/

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
	//empty constructor for an invalid command
	RPSCommand(): commandType(InvalidCommand) {}
	RPSCommand(CommandType commandType, PieceType pieceType, int fromX, int fromY, int toX, int toY, bool jokerInvolved,
			   int jokerX, int jokerY): commandType(commandType), pieceType(pieceType), fromX(fromX),
										fromY(fromY), toX(toX), toY(toY), jokerInvolved(jokerInvolved), jokerX(jokerX),
										jokerY(jokerY) {}
	CommandType getCommandType() { return this->commandType; };

	//getters and setters

	void setCommandType(CommandType commandType) { this->commandType = commandType; }
	PieceType getPieceType() { return this->pieceType; };
	void setPieceType(PieceType pieceType) { this->pieceType = pieceType; }
	int getfromX() { return this->fromX; };
	void setFromX(int fromX) { this->fromX = fromX; }
	int getfromY() { return this->fromY; };
	void setFromY(int fromY) { this->fromY = fromY; }
	int getToX() { return this->toX; };
	void setToX(int toX) { this->toX = toX; }
	int getToY() { return this->toY; };
	void setToY(int toY) { this->toY = toY; }
	bool isJokerInvolved() { return this->jokerInvolved; };
	void setJokerInvolved(bool jokerInvolved) { this->jokerInvolved = jokerInvolved; }
	int getJokerX() { return this->jokerX; };
	void setJokerX(int jokerX) { this->jokerX = jokerX; }
	int getJokerY() { return this->jokerY; };
	void setJokerY(int jokerY) { this->jokerY = jokerY; }
};

#endif /* RPSCOMMAND_H_ */
