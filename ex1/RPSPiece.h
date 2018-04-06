//
// Created by Roi Koren on 06/04/2018.
//

#ifndef RPSPIECE_H
#define RPSPIECE_H

#include <iostream>
#include <cstring>

enum PieceType {Rock, Paper, Scissors, Bomb, Flag};

class Piece {
        const bool isJoker;
        PieceType type;
        int player;

    public:
        Piece(PieceType type, bool isJoker, int player);
        std::string toString();
};

#endif //RPSPIECE_H
