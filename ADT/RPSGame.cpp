/*
 * RPSGame.cpp
 *
 *  Created on: 8 ���� 2018
 *      Author: user
 */


#include "RPSGame.h"


RPS_Massage Game::RPSSetPosition(RPSCommand command,int player){
	if(command.getPieceType() == Move ){
		return Invalid_Argument;
	}

	int toX = command.getToX();
	int toY = command.getToY();

	if(toX<1 || toX>M || toY<1 || toY>N){
		return Destinations_Out_Of_Range;
	}

	Piece newPiece = new Piece(command.getPieceType(), command.isJokerInvolved(),player);

	if(this->board[toX-1][toY-1] != NULL){
		if(this->board[toX][toY].player == player){
			return Bad_Position;
		}

		else{
			this->board[toX-1][toY-1]  = RPSPerformBattle(this->board[toX][toY],newPiece);
		}
	}

	else{
		this->board[toX-1][toY-1] = newPiece;
	}

	return Success;

}




RPS_Massage Game::RPSSetMove(RPSCommand command,int player){
	if(command.getPieceType() != Move ){
		return Invalid_Argument;
	}

	int fromX = command.getfromX();
	int fromY = command.getfromY();

	int toX = command.getToX();
	int toY = command.getToY();

	if(toX<1 || toX>M || toY<1 || toY>N){
		return Destinations_Out_Of_Range;
	}

	if(fromX<1 || fromX>M || fromY<1 || fromY>N){
		return Source_Out_Of_Range;
	}

	if(abs(toX-fromX)!=1 || abs(toY-fromY)!=1){
		return Illegal_Move;
	}

	if(this->board[fromY][fromX]==NULL){
		return No_Piece_In_Position;
	}

	Piece attacker = this->board[fromY][fromX];

	if(attacker.getPieceType() == Bomb ||attacker.getPieceType() == Flag){
		return Immovable_Piece_In_Position;
	}

	if(attacker.getPlayer!=player){
		return Opponent_Piece_In_Position;
	}

	if(this->board[toX][toY]!=NULL){
		Piece target = this->board[toY][toX];
		this->board[toY][toX] = RPSPerformBattle(attacker,target);
	}
	else{
		this->board[toY][toX] = attacker;
	}


	if(command.isJokerInvolved()){
		int jokerX = command.getJokerX();
		int jokerY = command.getJokerY();

		if(!this->board[jokerY][jokerX].isJoker()){
			return No_Joker_in_position;
		}

		if(command.getPieceType() == Flag){
			return Invalid_Joker_Assigning;
		}

		this->board[jokerY][jokerX].setPieceType(command.getPieceType());

	}

	return Success;
}

Piece Game::RPSPerformBattle(Piece piece1,Piece piece2){
	if(piece1.getPieceType() == piece2.getPieceType() ||
	   piece1.getPieceType()==Bomb || piece2.getPieceType()==Bomb){
		RPSExcludePiece(piece1);
		RPSExcludePiece(piece2);
		return NULL; //both are removed
	}

	else if(piece1.getPieceType() == Rock){
		if(piece2.getPieceType() == Paper){
			RPSExcludePiece(piece1);
			return piece2;
		}
		else{
			RPSExcludePiece(piece2);
			return piece1;
		}
	}

	else if(piece1.getPieceType() == Paper){
		if(piece2.getPieceType() == Scissors){
			RPSExcludePiece(piece1);
			return piece2;
		}
		else{
			RPSExcludePiece(piece2);
			return piece1;
		}
	}

	else if(piece1.getPieceType() == Scissors){
		if(piece2.getPieceType() == Rock){
			RPSExcludePiece(piece1);
			return piece2;
		}
		else{
			RPSExcludePiece(piece2);
			return piece1;
		}
	}

	else if(piece1.getPieceType() == Flag){ //the case where piece2==Flag was covered
		RPSExcludePiece(piece1);
		return piece2;
	}

	return NULL; //Shouldn't get here, all options covered

}

void Game::RPSExcludePiece(Piece piece){
	if(piece.isJoker){
		if(piece.player==1){
			this->player1Jokers--;
		}
		else{
			this->player2Jokers--;
		}

		return;
	}

	switch(piece.getPieceType()){
		case(Rock):
			if(piece.player==1){
				this->player1Rocks--;
			}
			else{
				this->player2Rocks--;
			}
			break;
		case(Paper):
			if(piece.player==1){
				this->player1Papers--;
			}
			else{
				this->player2Papers--;
			}
			break;
		case(Scissors):
			if(piece.player==1){
				this->player1Scissors--;
			}
			else{
				this->player2Scissors--;
			}
			break;
		case(Bomb):
			if(piece.player==1){
				this->player1Bombs--;
			}
			else{
				this->player2Bombs--;
			}
			break;
		case(Flag):
			if(piece.player==1){
				this->player1Flags--;
			}
			else{
				this->player2Flags--;
			}
			break;
	}
}

RPS_Message Game::RPSCheckWinner(){
	if(this->player1Flags == 0){
		this->winner = 2;
		return All_Flags_Captured;
	}
	if(this->player2Flags == 0){
		this->winner = 1;
		return All_Flags_Captured;
	}

	if(this->player2Rocks==0 && this->player2Scissors==0
			&& this->player2Bombs == 0 && this->player2Jokers == 0){
		this->winner = 1;
		return All_Moving_Pieces_Captured;
	}
	if(this->player1Rocks==0 && this->player1Scissors==0
			&& this->player1Bombs == 0 && this->player1Jokers == 0){
		this->winner = 2;
		return All_Moving_Pieces_Captured;
	}

	this->winner = 0;
	return No_Winner;
}

ostream& operator<<(ostream& out,Game game){
	int i,j;
	for(i=0; i<N; i++){
		for(j=0; j<M; j++){
			if(game.board[i][j] == NULL){
				out<<' ';
			}
			else{
				out<<game.board[i][j];		}
		}
		out<<endl;
	}
	return out;
}



