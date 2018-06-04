//
// Created by Roi Koren on 20/05/2018.
//

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

RSPPlayer_204057566::RSPPlayer_204057566() {
	// Assume opponent put all of his pieces
	this->opponentFlags = FLAGS;
	this->opponentBombs = BOMBS;
	this->opponentJokers = JOKERS;
	this->opponentRocks = ROCKS;
	this->opponentPapers = PAPERS;
	this->opponentScissors = SCISSORS;
}

void RSPPlayer_204057566::notifyOnInitialBoard(const Board& b, const std::vector<std::unique_ptr<FightInfo>>& fights) {
	for (int i = 1; i <= M; i++) {
		for (int j = 1; j <= N; j++) {
			if (b.getPlayer(RPSPoint(i, j)) != this->player) { // Save opponent positions
				this->board.setPiece(this->opponent, RPSPiece(NOT_JOKER, NOT_JOKER, this->opponent), i, j);
			}
		}
	}

	for (auto itr = fights.begin(); itr != fights.end(); itr++) {
		this->updateBoardByBattle(**itr);
	}
}

void RSPPlayer_204057566::notifyOnOpponentMove(const Move& move) { // Updated my board
	int fromX = move.getFrom().getX();
	int fromY = move.getFrom().getY();
	RPSPiece piece = this->board.getPiece(this->opponent, fromX, fromY);
	this->board.setPiece(this->opponent, RPSPiece(), fromX, fromY);
	this->board.setPiece(this->opponent, piece, move.getTo().getX(), move.getTo().getY());
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

std::unique_ptr<Move> RSPPlayer_204057566::getMove() {
	// If we can fight NOW, we will
	for (int i = 1; i <= M; i++) {
		for (int j = 1; j <= N; j++) {
			RPSPiece rpsPiece = this->board.getPiece(this->player, i, j);
			char piece = rpsPiece.getPieceType();
			if (piece == NONE || piece == 'B' || piece == 'F' || piece == INVALID_PIECE ||
				(piece == 'J'  && rpsPiece.getJokerRepresentation() == 'B')) {
				continue;
			}
			if (this->board.getPlayer(RPSPoint(i, j)) == this->player) {
				if (i - 1 > 0 && this->board.getPlayer(RPSPoint(i - 1, j)) == this->opponent) {
					this->board.setPiece(this->player, this->board.getPiece(this->player, 1, j), i - 1, j);
					this->board.setPiece(this->player, RPSPiece(), i, j);
					return std::make_unique<RPSMove>(RPSPoint(i, j), RPSPoint(i - 1, j));
				}
				if (i + 1 < M && this->board.getPlayer(RPSPoint(i + 1, j)) == this->opponent) {
					this->board.setPiece(this->player, this->board.getPiece(this->player, 1, j), i + 1, j);
					this->board.setPiece(this->player, RPSPiece(), i, j);
					return std::make_unique<RPSMove>(RPSPoint(i, j), RPSPoint(i + 1, j));
				}
				if (j - 1 > 0 && this->board.getPlayer(RPSPoint(i, j - 1)) == this->opponent) {
					this->board.setPiece(this->player, this->board.getPiece(this->player, 1, j), i, j - 1);
					this->board.setPiece(this->player, RPSPiece(), i, j);
					return std::make_unique<RPSMove>(RPSPoint(i, j), RPSPoint(i, j - 1));
				}
				if (j + 1 < N && this->board.getPlayer(RPSPoint(i, j + 1)) == this->opponent) {
					this->board.setPiece(this->player, this->board.getPiece(this->player, 1, j), i, j + 1);
					this->board.setPiece(this->player, RPSPiece(), i, j);
					return std::make_unique<RPSMove>(RPSPoint(i, j), RPSPoint(i, j + 1));
				}
			}
		}
	}

	// Can't fight, so just find an open spot and go there. Means we need to be lucky and land in the vicinity of the flag...
	for (int i = 1; i <= M; i++) {
		for (int j = 1; j <= N; j++) {
			RPSPiece rpsPiece = this->board.getPiece(this->player, i, j);
			char piece = rpsPiece.getPieceType();
			if (piece == NONE || piece == 'B' || piece == 'F' || piece == INVALID_PIECE ||
				(piece == 'J'  && rpsPiece.getJokerRepresentation() == 'B')) {
				continue;
			}
			if (i - 1 > 0 && this->board.getPlayer(RPSPoint(i - 1, j)) != this->player) {
				this->board.setPiece(this->player, this->board.getPiece(this->player, 1, j), i - 1, j);
				this->board.setPiece(this->player, RPSPiece(), i, j);
				return std::make_unique<RPSMove>(RPSPoint(i, j), RPSPoint(i - 1, j));
			}
			if (i + 1 <= M && this->board.getPlayer(RPSPoint(i + 1, j)) != this->player) {
				this->board.setPiece(this->player, this->board.getPiece(this->player, 1, j), i + 1, j);
				this->board.setPiece(this->player, RPSPiece(), i, j);
				return std::make_unique<RPSMove>(RPSPoint(i, j), RPSPoint(i + 1, j));
			}
			if (j - 1 > 0 && this->board.getPlayer(RPSPoint(i, j - 1)) != this->player) {
				this->board.setPiece(this->player, this->board.getPiece(this->player, 1, j), i, j - 1);
				this->board.setPiece(this->player, RPSPiece(), i, j);
				return std::make_unique<RPSMove>(RPSPoint(i, j), RPSPoint(i, j - 1));
			}
			if (j + 1 <= N && this->board.getPlayer(RPSPoint(i, j + 1)) != this->player) {
				this->board.setPiece(this->player, this->board.getPiece(this->player, 1, j), i, j + 1);
				this->board.setPiece(this->player, RPSPiece(), i, j);
				return std::make_unique<RPSMove>(RPSPoint(i, j), RPSPoint(i, j + 1));
			}
		}
	}

	return nullptr; // Shouldn't get here...
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