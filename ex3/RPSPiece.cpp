/*
 * RPSPiece.cpp
 *
 *  Created on: 4 April 2018
 *      Author: user
 */
#include "RPSPiece.h"

#define CAPITAL_TO_LOW(c) ((c) - 'A' + 'a')

RPSPiece& RPSPiece::operator=(const RPSPiece& otherPiece) { // Copy EVERYTHING
    if (&otherPiece == this) {
        return *this;
    }
    pieceType = otherPiece.pieceType;
    jokerRepresentation = otherPiece.jokerRepresentation;
    player = otherPiece.player;
    return *this;
}

std::ostream& operator<<(std::ostream &out, RPSPiece &rpsPiece) {
    int player = rpsPiece.getPlayer();
    char piece = rpsPiece.getPieceType();

    piece =  player == 1 ? piece : CAPITAL_TO_LOW(piece);
    out << piece;
    return out;
}
