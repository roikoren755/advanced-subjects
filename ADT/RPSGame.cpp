/*
 * RPSGame.cpp
 *
 *  Created on: 4 באפר 2018
 *      Author: user
 */
#include "RPSGame.h"


	RPS_Massage Game::RPSSetPosition(Command command,int player){
		if(command.getType == Move ){
			return Invalid_Argument;
		}

		int toX = command.getToX;
		int toY = command.getToY;
	
	if(toX<1 || toX>M || toY<1 || toY>N){
		return Index_Out_Of_Range;
	}

	if(this->board[toX][toY] != NULL){
		if(this->board[toX][toY].player == command.getPlayer){
			return Bad_Position;
		}

		if(this->board[toX][toY].player ==)
			return Success;
		}
	
	return Success;

	}
	
	


	RPS_Massage Game::RPSSetMove(Command command){
		if(command.getType == Position ){
			return Invalid_Argument;
		}

		int fromX = command.getfromX;
		int fromY = command.getfromY;

		int toX = command.getToX;
		int toY = command.getToY;

		Piece piece = this->board[fromX][fromY];

		return 0;
	}


