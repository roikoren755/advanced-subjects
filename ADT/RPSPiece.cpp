/*
 * RPSPiece.cpp
 *
 *  Created on: 4 April 2018
 *      Author: user
 */
#include "RPSPiece.h"
#define CAPITAL_TO_LOW(c) (c - 'A' + 'a')

ostream& operator<<(ostream &out, RPSPiece &rpsPiece) {
    int player = rpsPiece.getPlayer();
    char piece;
    switch (rpsPiece.getPieceType()) {
        case Rock:
            piece = 'R';
            break;
        case Paper:
            piece = 'P';
            break;
        case Scissors:
            piece = 'S';
            break;
        case Bomb:
            piece = 'B';
            break;
        case Flag:
            piece = 'F';
            break;
        default:
            piece = '_';
    }

    return out << player == 1 ? piece : CAPITAL_TO_LOW(piece);
}
