/*
 * RPSPiece.cpp
 *
 *  Created on: 4 ���� 2018
 *      Author: user
 */
#include <iostream>
#include <cstring>
#include "RPSPiece.h"

Piece::Piece():
        isJoker(false),type(None),player(NULL){}

Piece::Piece(PieceType type,bool isJoker,int player):isJoker(isJoker),type(type),player(player){}


ostream& operator<<(ostream& out,Piece piece){
    int player = piece.getPlayer();
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

int Piece::getPlayer(){
    return this->player;
}



