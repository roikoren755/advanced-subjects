/*
 * RPSCommand.h
 *
 *  Created on: 5 April 2018
 *      Author: user
 */

#ifndef RPSCOMMAND_H_
#define RPSCOMMAND_H_

#include "RPSPiece.h"
#include "RPSCommand.h"

#define N 10
#define M 10

enum RPS_Message {Success, Invalid_Argument, Bad_Position};

class Game {
    Piece board[N][M];
    Player currentPlayer;

    int player1Rocks;
    int player1Papers;
    int player1Scissors;
    int player1Bombs;
    int player1Jokers;
    int player1Flags;

    int player2Rocks;
    int player2Papers;
    int player2Scissors;
    int player2Bombs;
    int player2Jokers;
    int player2Flags;

public:
    RPS_Message RPSSetMove(Command command);
    RPS_Message RPSSetPosition(Command command);
};

#endif
