/*
 * RPSPiece.cpp
 *
 *  Created on: 4 April 2018
 *      Author: user
 */
#include "RPSPiece.h"

//easy conversion
#define CAPITAL_TO_LOW(c) (c - 'A' + 'a')

RPSPiece& RPSPiece::test() {
	std::cout << "TEST" << std::endl;
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
			case None:
				piece = ' ';
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
