//
// Created by Roi Koren on 20/05/2018.
//
#include <cmath>
#include "AlgorithmRegistration.h"
#include "RSPPlayer_204057566.h"
#include "RPSPoint.h"
#include "RPSPiecePosition.h"
#include "RPSMove.h"
#include "RPSJokerChange.h"

#define ROCKS 2
#define PAPERS 5
#define SCISSORS 1
#define BOMBS 2
#define JOKERS 2
#define FLAGS 1

#define CAPTURE_BONUS 20
#define FROM_X 0
#define FROM_Y 1
#define TO_X 2
#define TO_Y 3

RSPPlayer_204057566::RSPPlayer_204057566() {
	// Assume opponent put all of his pieces
	this->opponentFlags = FLAGS;
	this->opponentBombs = BOMBS;
	this->opponentJokers = JOKERS;
	this->opponentRocks = ROCKS;
	this->opponentPapers = PAPERS;
	this->opponentScissors = SCISSORS;
}

void RSPPlayer_204057566::updateOpponentPieces(char piece, int x, int y, int newX, int newY) {
	for (auto it = this->opponentPieces.begin(); it != this->opponentPieces.end(); it++) {
		if (it->first.getPosition().getX() == x && it->first.getPosition().getY() == y) {
			this->opponentPieces.erase(it);
			if (newX != -1 && newY != -1) {
				this->opponentPieces.emplace_back(std::make_pair(RPSPiecePosition(newX, newY, piece, INVALID_PIECE), true));
			}
		}
	}
}

double posDistance(int x0, int y0, int x1, int y1) {
	return sqrt(pow(x0 - x1, 2) + pow(y0 - y1, 2));
}

void RSPPlayer_204057566::notifyOnInitialBoard(const Board& b, const std::vector<std::unique_ptr<FightInfo>>& fights) {
	for (int i = 1; i <= M; i++) {
		for (int j = 1; j <= N; j++) {
			if (b.getPlayer(RPSPoint(i, j)) != this->player) { // Save opponent positions
				this->board.setPiece(this->opponent, RPSPiece(NOT_JOKER, NOT_JOKER, this->opponent), i, j);
				this->opponentPieces.emplace_back(std::make_pair(RPSPiecePosition(i, j, INVALID_PIECE, INVALID_PIECE), false));
			}
		}
	}

	for (auto itr = fights.begin(); itr != fights.end(); itr++) {
		this->updateBoardByBattle(**itr);
	}
}

void RSPPlayer_204057566::notifyOnOpponentMove(const Move& move) { // Updated my board
	this->movesCounter++;
	int fromX = move.getFrom().getX();
	int fromY = move.getFrom().getY();
	int toX = move.getTo().getX();
	int toY = move.getTo().getX();
	RPSPiece piece = this->board.getPiece(this->opponent, fromX, fromY);
	this->board.setPiece(this->opponent, RPSPiece(), fromX, fromY);
	this->board.setPiece(this->opponent, piece, toX, toY);
	updateOpponentPieces((piece.getPieceType() == 'J') ? piece.getJokerRepresentation(): piece.getPieceType(), fromX,
						 fromY, toX, toY);
}

void RSPPlayer_204057566::notifyFightResult(const FightInfo &fightInfo) {
	this->updateBoardByBattle(fightInfo);
}

void RSPPlayer_204057566::updateBoardByBattle(const FightInfo &fightInfo) {
	int x = fightInfo.getPosition().getX();
	int y = fightInfo.getPosition().getY();
	char opponentPiece = fightInfo.getPiece(this->opponent);
	int winner = fightInfo.getWinner();
	if (winner != this->player) { // Got information about opponent's piece
		this->board.setPiece(this->player, RPSPiece(), x, y);
		this->board.setPiece(this->opponent, RPSPiece(opponentPiece, NONE, this->opponent), x, y);
		updateOpponentPieces(opponentPiece, x, y, x, y); // change piece type
	}
	else { // One less to worry about
		switch (opponentPiece) {
			case 'J':
				this->opponentJokers--;
				break;
			case 'F':
				this->opponentFlags--;
				break;
			case 'B':
				this->opponentBombs--;
				break;
			case 'R':
				this->opponentRocks--;
				break;
			case 'P':
				this->opponentPapers--;
				break;
			case 'S':
				this->opponentScissors--;
				break;
			default:
				break;
		}

		this->board.setPiece(this->opponent, RPSPiece(), x, y); // Clear
		updateOpponentPieces(INVALID_PIECE, x, y, -1, -1); // erase
	}
}

void RSPPlayer_204057566::getInitialPositions(int player, std::vector<std::unique_ptr<PiecePosition>> &vectorToFill) {
	// Two clusters, one surrounding a flag, one a bomb, with 3 movable pieces spread about
	this->player = player;
	this->opponent = player == 1 ? 2 : 1;
	this->board.setPiece(player, RPSPiece('F', player), 8, 8);
	vectorToFill.emplace_back(std::make_unique<RPSPiecePosition>(8, 8, 'F', NOT_JOKER));
	this->board.setPiece(player, RPSPiece('P', player), 5, 3);
	vectorToFill.emplace_back(std::make_unique<RPSPiecePosition>(5, 3, 'P', NOT_JOKER));
	this->board.setPiece(player, RPSPiece('P', player), 5, 5);
	vectorToFill.emplace_back(std::make_unique<RPSPiecePosition>(5, 5, 'P', NOT_JOKER));
	this->board.setPiece(player, RPSPiece('P', player), 5, 7);
	vectorToFill.emplace_back(std::make_unique<RPSPiecePosition>(5, 7, 'P', NOT_JOKER));
	this->board.setPiece(player, RPSPiece('P', player), 8, 7);
	vectorToFill.emplace_back(std::make_unique<RPSPiecePosition>(8, 7, 'P', NOT_JOKER));
	this->board.setPiece(player, RPSPiece('P', player), 8, 9);
	vectorToFill.emplace_back(std::make_unique<RPSPiecePosition>(8, 9, 'P', NOT_JOKER));
	this->board.setPiece(player, RPSPiece('R', player), 4, 6);
	vectorToFill.emplace_back(std::make_unique<RPSPiecePosition>(4, 6, 'R', NOT_JOKER));
	this->board.setPiece(player, RPSPiece('R', player), 7, 5);
	vectorToFill.emplace_back(std::make_unique<RPSPiecePosition>(7, 5, 'R', NOT_JOKER));
	this->board.setPiece(player, RPSPiece('B', player), 4, 5);
	vectorToFill.emplace_back(std::make_unique<RPSPiecePosition>(4, 5, 'B', NOT_JOKER));
	this->board.setPiece(player, RPSPiece('B', player), 9, 8);
	vectorToFill.emplace_back(std::make_unique<RPSPiecePosition>(9, 8, 'B', NOT_JOKER));
	this->board.setPiece(player, RPSPiece('J', 'R', player), 3, 5);
	vectorToFill.emplace_back(std::make_unique<RPSPiecePosition>(3, 5, 'J', 'R'));
	this->board.setPiece(player, RPSPiece('J', 'S', player), 7, 8);
	vectorToFill.emplace_back(std::make_unique<RPSPiecePosition>(7, 8, 'J', 'S'));
	this->board.setPiece(player, RPSPiece('S', player), 4, 4);
	vectorToFill.emplace_back(std::make_unique<RPSPiecePosition>(4, 4, 'S', NOT_JOKER));
}

// return  1 if piece wins
//         0 if both die
//        -1 if enemy wins
int checkIfFightWinner(char piece, char enemy) {
	if (piece == enemy || piece == 'B' || enemy == 'B') {
		return 0;
	}
	else if (piece == 'R') {
		if (enemy == 'P') {
			return -1;
		}
		else {
			return 1;
		}
	}
	else if (piece == 'P') {
		if (enemy == 'S') {
			return -1;
		}
		else {
			return 1;
		}
	}
	else if (piece == 'S') {
		if (enemy == 'R') {
			return -1;
		}
		else {
			return 1;
		}
	}
	else if (piece == 'F') {
		return -1;
	}

	return 0; // default
}

double RSPPlayer_204057566::evaluateMove(char piece, int x, int y) {
	double score = INT32_MIN;
	double tempScore;
	int won;

	for (auto it = this->opponentPieces.begin(); it != this->opponentPieces.end(); it++) {
		tempScore = N - posDistance(it->first.getPosition().getX(), it->first.getPosition().getY(), x, y);
		if (it->first.getPiece() != INVALID_PIECE) {
			won = checkIfFightWinner(piece, it->first.getPiece());
			if (won > 0) {
				tempScore += CAPTURE_BONUS;
			} else if (won < 0) {
				tempScore = N - tempScore; //Prefer the distant ones
				tempScore -= CAPTURE_BONUS;
			}
		}
		if (!it->second) {  // if might be flag
			tempScore += this->movesCounter;
		}

		if (tempScore > score) {
			score = tempScore;
		}
	}

	return score;
}

std::unique_ptr<Move> RSPPlayer_204057566::getMove() {
	int fromX, fromY, toX, toY;
	double score = 0;
	double tempScore = 0;

	for (int i = 1; i <= M; i++) {
		for (int j = 1; j <= N; j++) {
			RPSPiece rpsPiece = this->board.getPiece(this->player, i, j);
			char piece = rpsPiece.getPieceType();
			if (piece == NONE || piece == 'B' || piece == 'F' || piece == INVALID_PIECE ||
				(piece == 'J' && rpsPiece.getJokerRepresentation() == 'B')) {
				continue;
			}
			if (i - 1 > 0 && this->board.getPlayer(RPSPoint(i - 1, j)) != this->player) {
				tempScore = this->evaluateMove(piece, i - 1, j);
				if (std::get<FROM_X>(prevMove) == i && std::get<FROM_Y>(prevMove) == j &&
				    std::get<TO_X>(prevMove) == i - 1 && std::get<TO_Y>(prevMove) == j) {
					tempScore = 0;
				}

				if (tempScore > score) {
					score = tempScore;
					fromX = i;
					fromY = j;
					toX = i - 1;
					toY = j;
				}
			}
			if (i + 1 <= M && this->board.getPlayer(RPSPoint(i + 1, j)) != this->player) {
				tempScore = this->evaluateMove(piece, i + 1, j);
				if (std::get<FROM_X>(prevMove) == i && std::get<FROM_Y>(prevMove) == j &&
				    std::get<TO_X>(prevMove) == i + 1 && std::get<TO_Y>(prevMove) == j) {
					tempScore = 0;
				}
				if (tempScore > score) {
					score = tempScore;
					fromX = i;
					fromY = j;
					toX = i + 1;
					toY = j;
				}
			}
			if (j - 1 > 0 && this->board.getPlayer(RPSPoint(i, j - 1)) != this->player) {
				tempScore = this->evaluateMove(piece, i, j - 1);
				if (std::get<FROM_X>(prevMove) == i && std::get<FROM_Y>(prevMove) == j &&
				    std::get<TO_X>(prevMove) == i && std::get<TO_Y>(prevMove) == j - 1) {
					tempScore = 0;
				}
				if (tempScore > score) {
					score = tempScore;
					fromX = i;
					fromY = j;
					toX = i;
					toY = j - 1;
				}
			}
			if (j + 1 <= N && this->board.getPlayer(RPSPoint(i, j + 1)) != this->player) {
				tempScore = this->evaluateMove(piece, i, j + 1);
				if (std::get<FROM_X>(prevMove) == i && std::get<FROM_Y>(prevMove) == j &&
				    std::get<TO_X>(prevMove) == i && std::get<TO_Y>(prevMove) == j + 1){
					tempScore = 0;
				}
				if (tempScore > score) {
					score = tempScore;
					fromX = i;
					fromY = j;
					toX = i;
					toY = j + 1;
				}
			}
		}
	}

	this->board.setPiece(this->player, this->board.getPiece(this->player, fromX, fromY), toX, toY);
	this->board.setPiece(this->player, RPSPiece(), fromX, fromY);

	this->prevMove = std::make_tuple(fromX, fromY, toX, toY);
	return std::make_unique<RPSMove>(RPSPoint(fromX, fromY), RPSPoint(toX, toY));
}

std::unique_ptr<JokerChange> RSPPlayer_204057566::getJokerChange() {
	// Change to bomb if there's a piece threatening
	for (int i = 1; i <= M; i++) {
		for (int j = 1; j <= N; j++) {
			RPSPiece rpsPiece = this->board.getPiece(this->player, i, j);
			char piece = rpsPiece.getPieceType();
			if (piece != 'J' || rpsPiece.getPlayer() != this->player || rpsPiece.getJokerRepresentation() == 'B') {
				continue;
			}
			if (this->board.getPlayer(RPSPoint(i - 1, j)) == this->opponent) {
				this->board.getPiece(this->player, i, j).setJokerRepresentation('B');
				return std::make_unique<RPSJokerChange>(RPSPoint(i, j), 'B');
			}
			if (this->board.getPlayer(RPSPoint(i + 1, j)) == this->opponent) {
				this->board.getPiece(this->player, i, j).setJokerRepresentation('B');
				return std::make_unique<RPSJokerChange>(RPSPoint(i, j), 'B');
			}
			if (this->board.getPlayer(RPSPoint(i, j - 1)) == this->opponent) {
				this->board.getPiece(this->player, i, j).setJokerRepresentation('B');
				return std::make_unique<RPSJokerChange>(RPSPoint(i, j), 'B');
			}
			if (this->board.getPlayer(RPSPoint(i, j + 1)) == this->opponent) {
				this->board.getPiece(this->player, i, j).setJokerRepresentation('B');
				return std::make_unique<RPSJokerChange>(RPSPoint(i, j), 'B');
			}
		}
	}

	// Just switch for the heck of it. Confuse the enemy
	for (int i = 1; i <= M; i++) {
		for (int j = 1; j <= N; j++) {
			RPSPiece rpsPiece = this->board.getPiece(this->player, i, j);
			char piece = rpsPiece.getPieceType();
			if (piece != 'J' || rpsPiece.getPlayer() != this->player) {
				continue;
			}
			char currentRepresentation = rpsPiece.getJokerRepresentation();
			char newRepresentation;
			switch (currentRepresentation) {
				case 'B':
				case 'S':
					newRepresentation = 'R';
					break;
				case 'R':
					newRepresentation = 'P';
					break;
				case 'P':
					newRepresentation = 'S';
					break;
				default:
					return nullptr;
			}

			this->board.getPiece(this->player, i, j).setJokerRepresentation(newRepresentation);
			return std::make_unique<RPSJokerChange>(i, j, newRepresentation);
		}
	}

	// Or not
	return nullptr;
}

extern "C" {
	REGISTER_ALGORITHM(204057566)
}
