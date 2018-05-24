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

RPS_Message RPSGame::setInitialPositions(std::vector<std::unique_ptr<PiecePosition>>& positions, int player) {
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
	int toX = position.getPosition().getX();
	int toY = position.getPosition().getY();

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
	if (this->board.getPlayer(RPSPoint(toX, toY)) == player) {
		return Bad_Position;
	}
	else {
		this->board.setPiece(player, RPSPiece(pieceType, position.getJokerRep(), player), toX, toY);
	}

	return Success;
}

RPS_Message RPSGame::setMove(std::unique_ptr<Move> move, int player) {
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

	if ((abs(toX - fromX) != 1 || toY != fromY) && (abs(toY - fromY) != 1 || toX != fromX)) {
		return Illegal_Move;
	}

	RPSPiece piece = this->board.getPiece(fromY,fromX);

	if (piece.getPieceType() == NONE) {
		return No_Piece_In_Position;
	}

	if (piece.getPlayer() != player) {
		return Opponent_Piece_In_Position;
	}

	if (piece.getPieceType() == 'B' || piece.getPieceType() == 'F') {
		return Immovable_Piece_In_Position;
	}

	if (this->board.getPlayer(RPSPoint(toX, toY)) == player) {
		return Illegal_Move;
	}
	else {
		this->board.setPiece(player, piece, toX, toY);
		this->board.setPiece(player, RPSPiece(), fromX, fromY);
	}

	if (this->board.getPiece(player == 1 ? 2 : 1, toX, toY).getPieceType() == NONE) {
		return Success;
	}

	return Battle_Required;
}

RPSFightInfo RPSGame::performBattle(int x, int y) {
	RPSPiece player1 = this->board.getPiece(1, x, y);
	RPSPiece player2 = this->board.getPiece(2, x, y);
	char player1Piece = player1.getPieceType();
	char player2Piece = player2.getPieceType();
	int winner;

	if (player1Piece == NONE || player2Piece == NONE) {
		return RPSFightInfo(0, 0, NONE, NONE, 0);
	}

	if (player1Piece == 'J') {
		player1Piece = player1.getJokerRepresentation();
	}

	if (player2Piece == 'J') {
		player2Piece = player2.getJokerRepresentation();
	}

	if (player1Piece == player2Piece || player2Piece == 'B' || player1Piece == 'B') {
		this->excludePiece(x, y, 1);
		this->excludePiece(x, y, 2);
		winner = 0;
	}
	else if (player1Piece == 'R') {
		if (player2Piece == 'P') {
			this->excludePiece(x, y, 1);
			winner = 2;
		}
		else {
			this->excludePiece(x, y, 2);
			winner = 1;
		}
	}
	else if (player1Piece == 'P') {
		if (player2Piece == 'S') {
			this->excludePiece(x, y, 1);
			winner = 2;
		}
		else {
			this->excludePiece(x, y, 2);
			winner = 2;
		}
	}
	else if (player1Piece == 'S') {
		if (player2Piece == 'R') {
			this->excludePiece(x, y, 1);
			winner = 2;
		}
		else {
			this->excludePiece(x, y, 2);
			winner = 1;
		}
	}
	else {
		this->excludePiece(x, y, 1);
		winner = 2;
		if (player2Piece == 'F') {
			this->excludePiece(x, y, 2);
			winner = 0;
		}
	}

	return RPSFightInfo(x, y, player1.getPieceType(), player2.getPieceType(), winner);
}

void RPSGame::excludePiece(int x, int y, int player) {
	RPSPiece piece = this->board.getPiece(player, x, y);
	this->board.setPiece(player, RPSPiece(), x, y);
	switch (piece.getPieceType()) {
		case 'J':
			player == 1 ? this->player1Jokers-- : this->player2Jokers--;
			break;
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
			break;
		default:
			break;
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

RPS_Message RPSGame::changeJokerRepresentation(std::unique_ptr<JokerChange> jokerChange) {
	if (jokerChange == nullptr) {
		return Success;
	}

	int x = jokerChange->getJokerChangePosition().getX();
	int y = jokerChange->getJokerChangePosition().getY();
	if (x < 0 || x > M || y < 0 || y > N) {
		return Bad_Position;
	}

	char newRepresentation = jokerChange->getJokerNewRep();
	switch (newRepresentation) {
		case 'B':
		case 'R':
		case 'P':
		case 'S':
			break;
		default:
			return Bad_Joker_Representation;
	}

	if (this->board.getPiece(jokerChange->getJokerChangePosition()).getPieceType() != 'J') {
		return No_Joker_in_position;
	}

	this->board.getPiece(jokerChange->getJokerChangePosition()).setJokerRepresentation(jokerChange->getJokerNewRep());

	return Success;
}

std::ostream& operator<<(std::ostream& out, RPSGame &game) {
	bool printed = false;
	for (int i = 1; i <= M; i++) {
		for (int j = 1; j <= N; j++) {
			for (int k = 1; k <= NUM_PLAYERS; k++){
				RPSPiece piece = game.board.getPiece(k, i, j);
				if (piece.getPieceType() != NONE) {
					out << piece;
					printed = true;
				}
			}

			if (!printed) {
				out << ' ';
			}

			printed = false;
		}

		out << std::endl;
	}

	return out;
}

int RPSGame::finishPositioningStage(std::vector<std::unique_ptr<FightInfo>>& vectorToFill) {
	for (int i = 1; i <= M; i++) {
		for (int j = 1; j <= N; j++) {
			if (this->board.getPiece(1, i, j).getPieceType() != NONE && this->board.getPiece(2, i, j).getPieceType() != NONE) {
				vectorToFill.emplace_back(std::make_unique<RPSFightInfo>(this->performBattle(i, j)));
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
