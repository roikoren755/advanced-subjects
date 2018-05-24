//
// Created by Roi Koren on 20/05/2018.
//

#include "RPSAutomaticPlayerAlgorithm.h"
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

RPSAutomaticPlayerAlgorithm::RPSAutomaticPlayerAlgorithm() {
	this->opponentFlags = FLAGS;
	this->opponentBombs = BOMBS;
	this->opponentJokers = JOKERS;
	this->opponentRocks = ROCKS;
	this->opponentPapers = PAPERS;
	this->opponentScissors = SCISSORS;
}

void RPSAutomaticPlayerAlgorithm::notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights) {
	for (int i = 1; i <= M; i++) {
		for (int j = 1; j <= N; j++) {
			if (b.getPlayer(RPSPoint(i, j)) != this->player) {
				this->board.setPiece(opponent, RPSPiece(NOT_JOKER, NOT_JOKER, opponent), i, j);
			}
		}
	}

	for (auto itr = fights.begin(); itr != fights.end(); itr++) {
		this->updateBoardByBattle(**itr);
	}
}

void RPSAutomaticPlayerAlgorithm::notifyOnOpponentMove(const Move& move) {
	int fromX = move.getFrom().getX();
	int fromY = move.getFrom().getY();
	RPSPiece piece = this->board.getPiece(opponent, fromX, fromY);
	this->board.setPiece(opponent, RPSPiece(), fromX, fromY);
	this->board.setPiece(opponent, piece, move.getTo().getX(), move.getTo().getY());
}

void RPSAutomaticPlayerAlgorithm::notifyFightResult(const FightInfo &fightInfo) {
	this->updateBoardByBattle(fightInfo);
}

void RPSAutomaticPlayerAlgorithm::updateBoardByBattle(const FightInfo &fightInfo) {
	int x = fightInfo.getPosition().getX();
	int y = fightInfo.getPosition().getY();
	char opponentPiece = fightInfo.getPiece(opponent);
	int winner = fightInfo.getWinner();
	if (winner != this->player) {
		this->board.setPiece(this->player, RPSPiece(), x, y);
		this->board.setPiece(this->opponent, RPSPiece(opponentPiece, NONE, opponent), x, y);
	}
	else {
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

		this->board.setPiece(opponent, RPSPiece(), x, y);
	}
}

void RPSAutomaticPlayerAlgorithm::getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>> &vectorToFill) {
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

unique_ptr<Move> RPSAutomaticPlayerAlgorithm::getMove() {
	for (int i = 1; i <= M; i++) {
		for (int j = 1; j <= N; j++) {
			RPSPiece rpsPiece = this->board.getPiece(player, i, j);
			char piece = rpsPiece.getPieceType();
			if (piece == NONE || piece == 'B' || piece == 'F' || piece == INVALID_PIECE ||
				(piece == 'J'  && rpsPiece.getJokerRepresentation() == 'B')) {
				continue;
			}
			if (this->board.getPlayer(RPSPoint(i, j)) == player) {
				if (i - 1 > 0 && this->board.getPlayer(RPSPoint(i - 1, j)) == opponent) {
					this->board.setPiece(player, this->board.getPiece(player, 1, j), i - 1, j);
					this->board.setPiece(player, RPSPiece(), i, j);
					return std::make_unique<RPSMove>(RPSPoint(i, j), RPSPoint(i - 1, j));
				}
				if (i + 1 < M && this->board.getPlayer(RPSPoint(i + 1, j)) == opponent) {
					this->board.setPiece(player, this->board.getPiece(player, 1, j), i + 1, j);
					this->board.setPiece(player, RPSPiece(), i, j);
					return std::make_unique<RPSMove>(RPSPoint(i, j), RPSPoint(i + 1, j));
				}
				if (j - 1 > 0 && this->board.getPlayer(RPSPoint(i, j - 1)) == opponent) {
					this->board.setPiece(player, this->board.getPiece(player, 1, j), i, j - 1);
					this->board.setPiece(player, RPSPiece(), i, j);
					return std::make_unique<RPSMove>(RPSPoint(i, j), RPSPoint(i, j - 1));
				}
				if (j + 1 < N && this->board.getPlayer(RPSPoint(i, j + 1)) == opponent) {
					this->board.setPiece(player, this->board.getPiece(player, 1, j), i, j + 1);
					this->board.setPiece(player, RPSPiece(), i, j);
					return std::make_unique<RPSMove>(RPSPoint(i, j), RPSPoint(i, j + 1));
				}
			}
		}
	}

	for (int i = 1; i <= M; i++) {
		for (int j = 1; j <= N; j++) {
			RPSPiece rpsPiece = this->board.getPiece(player, i, j);
			char piece = rpsPiece.getPieceType();
			if (piece == NONE || piece == 'B' || piece == 'F' || piece == INVALID_PIECE ||
				(piece == 'J'  && rpsPiece.getJokerRepresentation() == 'B') || rpsPiece.getPlayer() != player) {
				continue;
			}
			if (i - 1 > 0 && this->board.getPlayer(RPSPoint(i - 1, j)) != player) {
				this->board.setPiece(player, this->board.getPiece(player, 1, j), i - 1, j);
				this->board.setPiece(player, RPSPiece(), i, j);
				return std::make_unique<RPSMove>(RPSPoint(i, j), RPSPoint(i - 1, j));
			}
			if (i + 1 < M && this->board.getPlayer(RPSPoint(i + 1, j)) != player) {
				this->board.setPiece(player, this->board.getPiece(player, 1, j), i + 1, j);
				this->board.setPiece(player, RPSPiece(), i, j);
				return std::make_unique<RPSMove>(RPSPoint(i, j), RPSPoint(i + 1, j));
			}
			if (j - 1 > 0 && this->board.getPlayer(RPSPoint(i, j - 1)) != player) {
				this->board.setPiece(player, this->board.getPiece(player, 1, j), i, j - 1);
				this->board.setPiece(player, RPSPiece(), i, j);
				return std::make_unique<RPSMove>(RPSPoint(i, j), RPSPoint(i, j - 1));
			}
			if (j + 1 < N && this->board.getPlayer(RPSPoint(i, j + 1)) != player) {
				this->board.setPiece(player, this->board.getPiece(player, 1, j), i, j + 1);
				this->board.setPiece(player, RPSPiece(), i, j);
				return std::make_unique<RPSMove>(RPSPoint(i, j), RPSPoint(i, j + 1));
			}
		}
	}

	return nullptr; // Shouldn't get here...
}

unique_ptr<JokerChange> RPSAutomaticPlayerAlgorithm::getJokerChange() {
	for (int i = 1; i <= M; i++) {
		for (int j = 1; j <= N; j++) {
			RPSPiece rpsPiece = this->board.getPiece(player, i, j);
			char piece = rpsPiece.getPieceType();
			if (piece != 'J' || rpsPiece.getPlayer() != player || rpsPiece.getJokerRepresentation() == 'B') {
				continue;
			}
			if (this->board.getPlayer(RPSPoint(i - 1, j)) == opponent) {
				this->board.getPiece(player, i, j).setJokerRepresentation('B');
				return std::make_unique<RPSJokerChange>(RPSPoint(i, j), 'B');
			}
			if (this->board.getPlayer(RPSPoint(i + 1, j)) == opponent) {
				this->board.getPiece(player, i, j).setJokerRepresentation('B');
				return std::make_unique<RPSJokerChange>(RPSPoint(i, j), 'B');
			}
			if (this->board.getPlayer(RPSPoint(i, j - 1)) == opponent) {
				this->board.getPiece(player, i, j).setJokerRepresentation('B');
				return std::make_unique<RPSJokerChange>(RPSPoint(i, j), 'B');
			}
			if (this->board.getPlayer(RPSPoint(i, j + 1)) == opponent) {
				this->board.getPiece(player, i, j).setJokerRepresentation('B');
				return std::make_unique<RPSJokerChange>(RPSPoint(i, j), 'B');
			}
		}
	}

	for (int i = 1; i <= M; i++) {
		for (int j = 1; j <= N; j++) {
			RPSPiece rpsPiece = this->board.getPiece(player, i, j);
			char piece = rpsPiece.getPieceType();
			if (piece != 'J' || rpsPiece.getPlayer() != player) {
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

			this->board.getPiece(player, i, j).setJokerRepresentation(newRepresentation);
			return std::make_unique<RPSJokerChange>(i, j, newRepresentation);
		}
	}

	return nullptr;
}