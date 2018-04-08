#include <iostream>
#include <cstring>
using namespace std;

enum PieceType{None,Rock, Paper, Scissors, Bomb, Flag };

class Piece{
	const bool isJoker;
	PieceType type;
	int player;
public:

	Piece();
	Piece(PieceType type,bool isJoker,int player);

    friend ostream& operator<<(ostream& out,Piece piece);

};






