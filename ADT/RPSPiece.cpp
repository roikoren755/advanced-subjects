/*
 * RPSPiece.cpp
 *
 *  Created on: 4 April 2018
 *      Author: user
 */
#include "RPSPiece.h"

#define CAPITAL_TO_LOW(c) (c - 'A' + 'a')

RPSPiece& RPSPiece::operator=( const RPSPiece& otherPiece){
	if(&otherPiece == this){
		return *this;
	}
	pieceType = otherPiece.pieceType;
	isJoker = otherPiece.isJoker;
	player = otherPiece.player;
	return *this;
}

std::ostream& operator<<(std::ostream &out, RPSPiece &rpsPiece) {
    int player = rpsPiece.getPlayer();
    char piece;
    if (rpsPiece.isPieceJoker()) {
        piece = 'J';
    }
    else {
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
                break;
        }
    }

    piece =  player == 1 ? piece : CAPITAL_TO_LOW(piece);
    out << piece ;
    return out ;
}
