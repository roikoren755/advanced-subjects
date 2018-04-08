/*
 * RPSPiece.cpp
 *
 *  Created on: 4 באפר 2018
 *      Author: user
 */
#include <iostream>
#include <cstring>
#include "RPSPiece.h"

Piece::Piece(PieceType type,bool isJoker,int player):isJoker(isJoker),type(type),player(player){}


ostream& operator<<(ostream& out,Piece piece){
 char c = 'S';

 switch(piece.type){
     case(Rock):
        out<<'R'<<endl;
        break;
     case(Paper):
        out<<'P'<<endl;
        break;
     case(Scissors):
        out<<c;
        break;
     case(Bomb):
        out<<'B'<<endl;
        break;
     case(Flag):
        out<<'F'<<endl;
        break;
 }
 return out;
}


