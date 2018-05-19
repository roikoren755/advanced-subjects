/*
 * RPSGame.cpp
 *
 *  Created on: 8 April 2018
 *      Author: user
 */

#include "RPSGame.h"
#include "RPSBoard.h"
#include "RPSFightInfo.h"
#include <vector>

#define ROCKS 2
#define PAPERS 5
#define SCISSORS 1
#define BOMBS 2
#define JOKERS 2
#define FLAGS 1

#define ALL_FLAGS_CAPTURED (-2)
#define ALL_MOVING_PIECES_CAPTURED (-3)
#define LEGAL_TIE 0

RPS_Message RPSGame::setInitialPositions(std::vector<unique_ptr<PiecePosition>>& positions, int player) {
	RPS_Message message;
	for (auto itr = positions.begin(); itr != positions.end(); itr++) {
		message = this->setPosition(**itr, player);
		if (message != Success) {
			return message;
		}
	}

	return Success;
}


bool RPSGame::validateNumbersOfPieces(int player) {
	if (player == 1 && this->player1Rocks <= ROCKS && this->player1Papers <= PAPERS && this->player1Scissors <= SCISSORS
			&& this->player1Bombs <= BOMBS && this->player1Jokers <= JOKERS && this->player1Flags <= FLAGS) {
		return true;
	}

	return player == 2 && this->player2Rocks <= ROCKS && this->player2Papers <= PAPERS && this->player2Scissors <= SCISSORS
		&& this->player2Bombs <= BOMBS && this->player2Jokers <= JOKERS && this->player2Flags <= FLAGS;
}

bool RPSGame::validateNumberOfFlags(int player) {
	return (player == 1 ? this->player1Flags : this->player2Flags) == FLAGS;
}

RPS_Message RPSGame::setPosition(PiecePosition &position, int player) {
	Point positionPoint = position.getPosition();
	int toX = positionPoint.getX();
	int toY = positionPoint.getY();

	// checks the range
	if (toX < 1 || toX > M || toY < 1 || toY > N) {
			return Destination_Out_Of_Range;
	}

	// increment the counter
	char pieceType = position.getPiece();
	switch (pieceType) {
			case 'R':
				player == 1 ? this->player1Rocks++ : this->player2Rocks++;
				break;
			case 'P':
				player == 1 ? this->player1Papers++ : this->player2Papers++;
				break;
			case 'S':
				player == 1 ? this->player1Scissors++ : this->player2Scissors++;
				break;
			case 'B':
				player == 1 ? this->player1Bombs++ : this->player2Bombs++;
				break;
			case 'F':
				player == 1 ? this->player1Flags++ : this->player2Flags++;
				break;
			case 'J':
				player == 1 ? this->player1Jokers++ : this->player2Jokers++;
				break;
			default:
				return Invalid_Argument;
	}


	// check if valid
	if (!validateNumbersOfPieces(player)) {
		return Too_Many_Pieces;
	}

	// check if there is a piece
	if (this->board.getPiece(toX, toY).getPlayer() == player) {
		return Bad_Position;
	}
	else {
		this->board.board[player - 1][toY - 1][toX - 1] = RPSPiece(pieceType, position.getJokerRep(), player);
	}

	return Success;
}

RPS_Message RPSGame::setMove(unique_ptr<Move> move, int player) {
	int fromX = (*move).getFrom().getX();
	int fromY = (*move).getFrom().getY();

	int toX = (*move).getTo().getX();
	int toY = (*move).getTo().getY();

	if (toX < 1 || toX > M || toY < 1 || toY > N) {
		return Destination_Out_Of_Range;
	}

	if (fromX < 1 || fromX > M || fromY < 1 || fromY > N) {
		return Source_Out_Of_Range;
	}

	if ( !( (abs(toX - fromX) == 1 && toY == fromY) || (abs(toY - fromY) == 1 && toX == fromX) ) ){ // TODO - fix? what is this?
		return Illegal_Move;
	}

	RPSPiece attacker = this->board.getPiece(fromY,fromX);
	if (attacker.getPieceType() == NONE) {
		return No_Piece_In_Position;
	}

	else if (attacker.getPieceType() == 'B' || attacker.getPieceType() == 'F') {
		return Immovable_Piece_In_Position;
	}

	int opponent = player == 1 ? 2 : 1;
	if (this->board.board[opponent - 1][toY - 1][toX - 1].getPieceType() != NONE) {
		this->performBattle(fromX, fromY, toX, toY, player, opponent);
	}
	else {
		this->board.board[player - 1][toY - 1][toX - 1] = attacker;
		this->board.board[player - 1][fromY - 1][fromX - 1] = RPSPiece();
	}

	return this->checkWinner();
}

FightInfo RPSGame::performBattle(int x, int y) {
	RPSPiece attacker = this->board.board[0][y - 1][x - 1];
	RPSPiece defender = this->board.board[1][y - 1][x - 1];
	char attackerType = attacker.getPieceType();
	char defenderType = defender.getPieceType();
	int winner;

	if (attackerType == defenderType || defenderType == 'B' || attackerType == 'B') {
		this->excludePiece(fromX, fromY, player);
		this->excludePiece(toX, toY, opponent);
		winner = 0;
	}
	else if (attackerType == 'R') {
		if (defenderType == 'P') {
			this->excludePiece(fromX, fromY, player);
			winner =
		}
		else {
			this->excludePiece(toX, toY, opponent);
			this->board.board[player - 1][fromY - 1][fromX - 1] = RPSPiece();
			this->board.board[player - 1][toY - 1][toX - 1] = attacker;
		}
	}
	else if (attackerType == 'P') {
		if (defenderType == 'S') {
			this->excludePiece(fromX, fromY, player);
		}
		else {
			this->excludePiece(toX, toY, opponent);
			this->board.board[player - 1][fromY - 1][fromX - 1] = RPSPiece();
			this->board.board[player - 1][toY - 1][toX - 1] = attacker;
		}
	}
	else if (attackerType == 'S') {
		if (defenderType == 'R') {
			this->excludePiece(fromX, fromY, player);
		}
		else {
			this->excludePiece(toX, toY, opponent);
			this->board.board[player - 1][fromY - 1][fromX - 1] = RPSPiece();
			this->board.board[player - 1][toY - 1][toX - 1] = attacker;
		}
	}
	else {
		this->excludePiece(fromX, fromY, player);
		if (defenderType == 'F') {
			this->excludePiece(toX, toY, opponent);
		}
	}
}

void RPSGame::excludePiece(int x, int y, int player) {
	RPSPiece piece = this->board.board[player - 1][y - 1][x - 1];
	this->board.board[player - 1][y - 1][x - 1] = RPSPiece();
	if (piece.getPieceType() == 'J') {
		player == 1 ? this->player1Jokers-- : this->player2Jokers--;
	}
	else { // check the piece type and decrease counter
		switch (piece.getPieceType()) {
			case 'R':
				player == 1 ? this->player1Rocks-- : this->player2Rocks--;
				break;
			case 'P':
				player == 1 ? this->player1Papers-- : this->player2Papers--;
				break;
			case 'S':
				player == 1 ? this->player1Scissors-- : this->player2Scissors--;
				break;
			case 'B':
				player == 1 ? this->player1Bombs-- : this->player2Bombs--;
				break;
			case 'F':
				player == 1 ? this->player1Flags-- : this->player2Flags--;
			default:
				break;
		}
	}
}

RPS_Message RPSGame::checkWinner() {
	// check if out of flags
	if (!this->player1Flags) {
		this->winner = 2;
		return All_Flags_Captured;
	}
	if (!this->player2Flags) {
		this->winner = 1;
		return All_Flags_Captured;
	}

	// check if moving pieces re gone
	if (!this->player2Rocks && !this->player2Papers && !this->player2Scissors && !this->player2Bombs
		&& !this->player2Jokers) {
		this->winner = 1;
		return All_Moving_Pieces_Captured;
	}
	if (!this->player1Rocks && !this->player1Papers && !this->player1Scissors && !this->player1Bombs
		&& !this->player1Jokers) {
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
				if (game.board.board[k][i][j].getPieceType() != NONE) {
					out << game.board.board[k][i][j];
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

	return out;
}

int RPSGame::finishPositioningStage() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (this->board.board[0][i][j].getPieceType() != NONE && this->board.board[1][i][j].getPieceType() != NONE) {
				this->performBattle(j + 1, i + 1, j + 1, i + 1, 1, 2);
			}
		}
	}

	int ret;
	if (!this->player1Flags) {
		ret = ALL_FLAGS_CAPTURED;
		if (!this->player2Flags) {
			this->setWinner(0);
		}
		else {
			this->setWinner(2);
		}
	}
	else if (!this->player2Flags) {
		this->setWinner(1);
		ret = ALL_FLAGS_CAPTURED;
	}
	else if (!this->player1Rocks && !this->player1Papers && !this->player1Scissors && !this->player1Bombs
			 && !this->player1Jokers) {
		ret = ALL_MOVING_PIECES_CAPTURED;
		if (!this->player2Rocks && !this->player2Papers && !this->player2Scissors && !this->player2Bombs
			&& !this->player2Jokers) {
			this->setWinner(0);
		}
		else {
			this->setWinner(2);
		}
	}
	else if (!this->player2Rocks && !this->player2Papers && !this->player2Scissors && !this->player2Bombs && !this->player2Jokers) {
		ret = ALL_MOVING_PIECES_CAPTURED;
		this->setWinner(1);
	}
	else {
		this->setWinner(0);
		ret = LEGAL_TIE;
	}

	return ret;
}
