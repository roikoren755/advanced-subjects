/*
 * RPSGame.cpp
 *
 *  Created on: 8 April 2018
 *      Author: user
 */

#include "RPSGame.h"

#define ROCKS 2
#define PAPERS 5
#define SCISSORS 1
#define BOMBS 2
#define JOKERS 2
#define FLAGS 1

#define ALL_FLAGS_CAPTURED -2
#define ALL_MOVING_PIECES_CAPTURED -3
#define LEGAL_TIE 0

bool RPSGame::rpsValidateNumbersOfPieces(int player) {
	if (player == 1 && this->player1Rocks <= ROCKS && this->player1Papers <= PAPERS && this->player1Scissors <= SCISSORS
			&& this->player1Bombs <= BOMBS && this->player1Jokers <= JOKERS && this->player1Flags <= FLAGS) {
		return true;
	}

	if (player == 2 && this->player2Rocks <= ROCKS && this->player2Papers <= PAPERS && this->player2Scissors <= SCISSORS
		&& this->player2Bombs <= BOMBS && this->player2Jokers <= JOKERS && this->player2Flags <= FLAGS) {
		return true;
	}

	return false;
}

bool RPSGame::rpsValidateNumberOfJokers(int player) {
	return (player == 1 ? this->player1Flags : this->player2Flags) == FLAGS;
}

RPS_Message RPSGame::rpsSetPosition(RPSCommand &command, int player) {
	if (command.getCommandType() != Position) {
		return Invalid_Argument;
	}

	int toX = command.getToX();
	int toY = command.getToY();

	if (toX < 1 || toX > M || toY < 1 || toY > N) {
		return Destination_Out_Of_Range;
	}

	PieceType pieceType = command.getPieceType();
	if (command.isJokerInvolved()) {
		player == 1 ? this->player1Jokers++ : this->player2Jokers++;
	}
	else {
		switch (pieceType) {
			case Rock:
				player == 1 ? this->player1Rocks++ : this->player2Rocks++;
				break;
			case Paper:
				player == 1 ? this->player1Papers++ : this->player2Papers++;
				break;
			case Scissors:
				player == 1 ? this->player1Scissors++ : this->player2Scissors++;
				break;
			case Bomb:
				player == 1 ? this->player1Bombs++ : this->player2Bombs++;
				break;
			case Flag:
				player == 1 ? this->player1Flags++ : this->player2Flags++;
				break;
			default:
				return Invalid_Argument;
		}
	}

	if (!rpsValidateNumbersOfPieces(player)) {
		return Too_Many_Pieces;
	}

	if (this->boards[player - 1][toY - 1][toX - 1].getPieceType() != None) {
			return Bad_Position;
	}
	else {
		this->boards[player - 1][toY - 1][toX - 1] = RPSPiece(command.getPieceType(), command.isJokerInvolved(), player);
	}

	return Success;
}

RPS_Message RPSGame::rpsSetMove(RPSCommand &command, int player) {
	if (command.getCommandType() != Move) {
		return Invalid_Argument;
	}

	int fromX = command.getfromX();
	int fromY = command.getfromY();

	int toX = command.getToX();
	int toY = command.getToY();

	if (toX < 1 || toX > M || toY < 1 || toY > N) {
		return Destination_Out_Of_Range;
	}

	if (fromX < 1 || fromX > M || fromY < 1 || fromY > N) {
		return Source_Out_Of_Range;
	}

	if ( !( (abs(toX - fromX) == 1 && toY == fromY) || (abs(toY - fromY) == 1 && toX == fromX) ) ){
		return Illegal_Move;
	}

	RPSPiece attacker = this->boards[player - 1][fromY - 1][fromX - 1];
	if (attacker.getPieceType() == None) {
		return No_Piece_In_Position;
	}

	else if (attacker.getPieceType() == Bomb || attacker.getPieceType() == Flag) {
		return Immovable_Piece_In_Position;
	}

	int opponent = player == 1 ? 2 : 1;
	if (this->boards[opponent - 1][toY - 1][toX - 1].getPieceType() != None) {
		this->rpsPerformBattle(fromX, fromY, toX, toY, player, opponent);
	}
	else {
		this->boards[player - 1][toY - 1][toX - 1] = attacker;
		this->boards[player - 1][fromY - 1][fromX - 1] = RPSPiece();
	}

	if (command.isJokerInvolved()) {
		int jokerX = command.getJokerX();
		int jokerY = command.getJokerY();

		if (!this->boards[player - 1][jokerY - 1][jokerX - 1].isPieceJoker()) {
			return No_Joker_in_position;
		}

		if (command.getPieceType() == Flag) {
			return Invalid_Joker_Assigning;
		}

		this->boards[player - 1][jokerY - 1][jokerX - 1].setPieceType(command.getPieceType());
	}

	return this->rpsCheckWinner();
}

void RPSGame::rpsPerformBattle(int fromX, int fromY, int toX, int toY, int player, int opponent) {
	RPSPiece attacker = this->boards[player - 1][fromY - 1][fromX - 1];
	RPSPiece defender = this->boards[opponent - 1][toY - 1][toX - 1];
	PieceType attackerType = attacker.getPieceType();
	PieceType defenderType = defender.getPieceType();
	if (attackerType == defenderType || defenderType == Bomb || attackerType == Bomb) {
		this->rpsExcludePiece(fromX, fromY, player);
		this->rpsExcludePiece(toX, toY, opponent);
	}
	else if (attackerType == Rock) {
		if (defenderType == Paper) {
			this->rpsExcludePiece(fromX, fromY, player);
		}
		else {
			this->rpsExcludePiece(toX, toY, opponent);
			this->boards[player - 1][fromY - 1][fromX - 1] = RPSPiece();
			this->boards[player - 1][toY - 1][toX - 1] = attacker;
		}
	}
	else if (attackerType == Paper) {
		if (defenderType == Scissors) {
			this->rpsExcludePiece(fromX, fromY, player);
		}
		else {
			this->rpsExcludePiece(toX, toY, opponent);
			this->boards[player - 1][fromY - 1][fromX - 1] = RPSPiece();
			this->boards[player - 1][toY - 1][toX - 1] = attacker;
		}
	}
	else if (attackerType == Scissors) {
		if (defenderType == Rock) {
			this->rpsExcludePiece(fromX, fromY, player);
		}
		else {
			this->rpsExcludePiece(toX, toY, opponent);
			this->boards[player - 1][fromY - 1][fromX - 1] = RPSPiece();
			this->boards[player - 1][toY - 1][toX - 1] = attacker;
		}
	}
	else {
		this->rpsExcludePiece(fromX, fromY, player);
		if (defenderType == Flag) {
			this->rpsExcludePiece(toX, toY, opponent);
		}
	}
}

void RPSGame::rpsExcludePiece(int x, int y, int player) {
	RPSPiece piece = this->boards[player - 1][y - 1][x - 1];
	this->boards[player - 1][y - 1][x - 1] = RPSPiece();
	if (piece.isPieceJoker()) {
		player == 1 ? this->player1Jokers-- : this->player2Jokers--;
	}
	else {
		switch (piece.getPieceType()) {
			case Rock:
				player == 1 ? this->player1Rocks-- : this->player2Rocks--;
				break;
			case Paper:
				player == 1 ? this->player1Papers-- : this->player2Papers--;
				break;
			case Scissors:
				player == 1 ? this->player1Scissors-- : this->player2Scissors--;
				break;
			case Bomb:
				player == 1 ? this->player1Bombs-- : this->player2Bombs--;
				break;
			case Flag:
				player == 1 ? this->player1Flags-- : this->player2Flags--;
			default:
				break;
		}
	}
}

RPS_Message RPSGame::rpsCheckWinner() {
	if (!this->player1Flags) {
		this->winner = 2;
		return All_Flags_Captured;
	}
	if (!this->player2Flags) {
		this->winner = 1;
		return All_Flags_Captured;
	}

	if (!this->player2Rocks && !this->player2Scissors && !this->player2Bombs && !this->player2Jokers) {
		this->winner = 1;
		return All_Moving_Pieces_Captured;
	}
	if (!this->player1Rocks && !this->player1Scissors && !this->player1Bombs && !this->player1Jokers) {
		this->winner = 2;
		return All_Moving_Pieces_Captured;
	}

	this->winner = 0;
	return No_Winner;
}

std::ostream& operator<<(std::ostream& out, RPSGame &game) {
	bool printed = false;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			for (int k = 0; k < NUM_PLAYERS; k++){
				if (game.boards[k][i][j].getPieceType() != None) {
					out << game.boards[k][i][j];
					printed = true;
				}
			}
			if (!printed) {
				out << ' ';
				printed = false;
			}
			printed = false;

		}
		out << std::endl;
	}
	out << std::endl;
	return out;
}

int RPSGame::rpsFinishPositioningStage() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (this->boards[0][i][j].getPieceType() != None && this->boards[1][i][j].getPieceType() != None) {
				this->rpsPerformBattle(j + 1, i + 1, j + 1, i + 1, 1, 2);
			}
		}
	}

	int ret;
	if (!this->player1Flags) {
		ret = ALL_FLAGS_CAPTURED;
		if (!this->player2Flags) {
			this->rpsSetWinner(0);
		}
		else {
			this->rpsSetWinner(2);
		}
	}
	else if (!this->player2Flags) {
		this->rpsSetWinner(1);
		ret = ALL_FLAGS_CAPTURED;
	}
	else if (!this->player1Rocks && !this->player1Scissors && !this->player1Bombs && !this->player1Jokers) {
		ret = ALL_MOVING_PIECES_CAPTURED;
		if (!this->player2Rocks && !this->player2Scissors && !this->player2Bombs && !this->player2Jokers) {
			this->rpsSetWinner(0);
		}
		else {
			this->rpsSetWinner(2);
		}
	}
	else if (!this->player2Rocks && !this->player2Scissors && !this->player2Bombs && !this->player2Jokers) {
		ret = ALL_MOVING_PIECES_CAPTURED;
		this->rpsSetWinner(1);
	}
	else {
		this->rpsSetWinner(0);
		ret = LEGAL_TIE;
	}

	return ret;
}
