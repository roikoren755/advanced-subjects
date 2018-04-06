/*
 * RPSCommand.h
 *
 *  Created on: 5 April 2018
 *      Author: user
 */

#ifndef RPSCOMMAND_H_
#define RPSCOMMAND_H_

#include "RPSPiece.h"

#define N 10
#define M 10

enum CommandType {Position, Move, Invalid};

class RPSCommand {
    CommandType type;
    PieceType pieceType;
    int toX;
    int toY;
    int fromX;
    int fromY;
    int jokerX;
    int jokerY;

public:
    RPSCommand(std::string const& command);
    CommandType getType();
    PieceType getPieceType();
    int getFromX();
    int getFromY();
    int getToX();
    int getToY();
    int getJokerX();
    int getJokerY();
    int getLine;
};

#endif /* RPSCOMMAND_H_ */