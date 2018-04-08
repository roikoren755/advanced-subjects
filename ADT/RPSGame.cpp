/*
 * RPSGame.cpp
 *
 *  Created on: 8 באפר 2018
 *      Author: user
 */


#include "RPSGame.h"


	RPS_Massage Game::RPSSetPosition(Command command,int player){
		if(command.getType() == Move ){
			return Invalid_Argument;
		}

		int toX = command.getToX();
		int toY = command.getToY();

		if(toX<1 || toX>M || toY<1 || toY>N){
			return Index_Out_Of_Range;
		}

		Piece newPiece = new Piece(command.getPieceType(), command.isJokerInvolved(),command.getPlayer()));

		if(this->board[toX-1][toY-1] != NULL){
			if(this->board[toX][toY].player == command.getPlayer){
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




	RPS_Massage Game::RPSSetMove(Command command){
		if(command.getType() == Position ){
			return Invalid_Argument;
		}

		int fromX = command.getfromX();
		int fromY = command.getfromY();

		int toX = command.getToX();
		int toY = command.getToY();

		Piece attacker = this->board[fromX][fromY];
		Piece target = this->board[toX][toY];


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



