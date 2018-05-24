//
// Created by user on 04/05/2018.
//

#include "RPSFilePlayerAlgorithm.h"
#include <iostream>
#include <fstream>

#define MAXIMUM_LINE_LENGTH 1024
#define DELIMITERS " \t\n"

int getPositiveInt(const char* const integer) {
	int result = 0;
	int i = 0;
	while (integer && integer[i] >= '0' && integer[i] <= '9') {
		result *= 10;
		result += integer[i] - '0';
		i++;
	}

	return result;
}

RPSPiecePosition getRPSPiecePositionFromLine(const std::string& line) {
	char buffer[MAXIMUM_LINE_LENGTH + 1];
	int x = 0;
	int y = 0;
	char piece = INVALID_PIECE;
	char jokerRepresentation = INVALID_PIECE;
	bool jokerInvolved = false;
	if (!strcpy(buffer, line.c_str())) {
		return RPSPiecePosition(x, y, piece, jokerRepresentation);
	}

	char* argument = strtok(buffer, DELIMITERS);
	if (argument && argument[0] > 'A' && argument[0] < 'Z' && !argument[1]) {
		switch (argument[0]) {
			case 'J':
				jokerInvolved = true;
			case 'B':
			case 'F':
			case 'P':
			case 'R':
			case 'S':
				piece = argument[0];
				break;
			default:
				break;
		}

		argument = strtok(nullptr, DELIMITERS);
		if (!argument || (x = getPositiveInt(argument)) < 1) {
			piece = INVALID_PIECE;
		}

		argument = strtok(nullptr, DELIMITERS);
		if (!argument || (y = getPositiveInt(argument)) < 1) {
			piece = INVALID_PIECE;
		}

		if (jokerInvolved) {
			argument = strtok(nullptr, DELIMITERS);
			if (!argument || argument[1]) {
				piece = INVALID_PIECE;
			}
			else {
				switch (argument[0]) {
					case 'B':
					case 'P':
					case 'R':
					case 'S':
						jokerRepresentation = argument[0];
						break;
					default:
						piece = INVALID_PIECE;
						break;
				}
			}
		}
	}

	if (strtok(nullptr, DELIMITERS)) {
		piece = INVALID_PIECE;
	}

	return RPSPiecePosition(x, y, piece, jokerRepresentation);
}

std::pair<std::unique_ptr<RPSMove>, std::unique_ptr<RPSJokerChange>> getRPSMoveAndJokerChangePairFromLine(const std::string& line) {
	char buffer[MAXIMUM_LINE_LENGTH + 1];
	if (!strcpy(buffer, line.c_str())) {
		return std::make_pair(nullptr, nullptr);
	}

	int fromX = 0;
	int fromY = 0;
	int toX = 0;
	int toY = 0;
	bool jokerInvolved = false;
	int jokerY = 0;
	int jokerX = 0;
	char jokerRepresentation = INVALID_PIECE;

	char* argument = strtok(buffer, DELIMITERS);
	if (!argument) {
		return std::make_pair(nullptr, nullptr);
	}

	if (argument[0] > '0' && argument[0] <= '9') {
		if ((fromX = getPositiveInt(argument)) < 1) {
			return std::make_pair(std::make_unique<RPSMove>(fromX, fromY, toX, toY), nullptr);
		}

		argument = strtok(nullptr, DELIMITERS);
		if (!argument || (fromY = getPositiveInt(argument)) < 1) {
			return std::make_pair(std::make_unique<RPSMove>(fromX, fromY, toX, toY), nullptr);
		}

		argument = strtok(nullptr, DELIMITERS);
		if (!argument || (toX = getPositiveInt(argument)) < 1) {
			return std::make_pair(std::make_unique<RPSMove>(fromX, fromY, toX, toY), nullptr);
		}

		argument = strtok(nullptr, DELIMITERS);
		if (!argument || (toY = getPositiveInt(argument)) < 1) {
			return std::make_pair(std::make_unique<RPSMove>(fromX, fromY, toX, toY), nullptr);
		}

		argument = strtok(nullptr, DELIMITERS);
		if (argument) {
			if (!strcmp(argument, "J:")) {
				jokerInvolved = true;
				argument = strtok(nullptr, DELIMITERS);
				if (!argument || (jokerX = getPositiveInt(argument)) < 1) {
					return std::make_pair(std::make_unique<RPSMove>(fromX, fromY, toX, toY),
					        std::make_unique<RPSJokerChange>(jokerX, jokerY, jokerRepresentation));
				}

				argument = strtok(nullptr, DELIMITERS);
				if (!argument || (jokerY = getPositiveInt(argument)) < 1) {
					return std::make_pair(std::make_unique<RPSMove>(fromX, fromY, toX, toY),
										  std::make_unique<RPSJokerChange>(jokerX, jokerY, jokerRepresentation));
				}

				argument = strtok(nullptr, DELIMITERS);
				if (!argument || argument[1]) {
					return std::make_pair(std::make_unique<RPSMove>(fromX, fromY, toX, toY),
										  std::make_unique<RPSJokerChange>(jokerX, jokerY, jokerRepresentation));
				}
				else {
					switch (argument[0]) {
						case 'B':
						case 'P':
						case 'R':
						case 'S':
							jokerRepresentation = argument[0];
							break;
						default:
							jokerRepresentation = INVALID_PIECE;
							break;
					}
				}
			}
		}
	}

	if (strtok(nullptr, DELIMITERS)) {
		fromX = 0;
		return std::make_pair(std::make_unique<RPSMove>(fromX, fromY, toX, toY),
							  std::make_unique<RPSJokerChange>(jokerX, jokerY, jokerRepresentation));
	}

	return std::make_pair(std::make_unique<RPSMove>(fromX, fromY, toX, toY),
	        jokerInvolved ? std::make_unique<RPSJokerChange>(jokerX, jokerY, jokerRepresentation) : nullptr);
}

RPSFilePlayerAlgorithm::RPSFilePlayerAlgorithm(int player, const std::string& initialPositionsFile, const std::string& movesFile) {
	if (player != 1 && player != 2) {
		return;
	}

	this->player = player;
	this->loadInitialPositionsFromFile(initialPositionsFile);
	this->loadMovesAndJokerChangesFromFile(movesFile);
}

void RPSFilePlayerAlgorithm::loadInitialPositionsFromFile(const std::string& initialPositionsFile) {
	std::ifstream initialPositionsFileStream;
	initialPositionsFileStream.open(initialPositionsFile);

	std::string line;
	if (initialPositionsFileStream.is_open()) {
		while (std::getline(initialPositionsFileStream, line)) {
			this->initialPositions.emplace_back(std::make_unique<RPSPiecePosition>(getRPSPiecePositionFromLine(line)));
		}

		initialPositionsFileStream.close();
	}

	else {
		this->initialPositions.emplace_back(nullptr);
	}
}

void RPSFilePlayerAlgorithm::loadMovesAndJokerChangesFromFile(const std::string& movesAndJokerChangesFile) {
	std::ifstream movesAndJokerChangesFileStream;
	movesAndJokerChangesFileStream.open(movesAndJokerChangesFile);

	std::string line;
	if (movesAndJokerChangesFileStream.is_open()) {
		while (std::getline(movesAndJokerChangesFileStream, line)) {
			this->movesAndJokerChanges.emplace_back(getRPSMoveAndJokerChangePairFromLine(line));
		}

		movesAndJokerChangesFileStream.close();
	}

	else {
		this->movesAndJokerChanges.emplace_back(std::pair<std::unique_ptr<RPSMove>, std::unique_ptr<RPSJokerChange>>(nullptr, nullptr));
	}
}

void RPSFilePlayerAlgorithm::getInitialPositions(int player, std::vector<std::unique_ptr<PiecePosition>>& vectorToFill) {
	if (player != this->player) {
		return;
	}
	auto numberOfPieces = (int) this->initialPositions.size();
	for (int i = 0; i < numberOfPieces; i++) {
		vectorToFill.emplace_back(std::move(this->initialPositions.front()));
		this->initialPositions.erase(this->initialPositions.begin());
	}
}

std::unique_ptr<Move> RPSFilePlayerAlgorithm::getMove() {
	if (this->turn) {
		this->movesAndJokerChanges.erase(this->movesAndJokerChanges.begin());
	}
	this->turn++;
	if (this->movesAndJokerChanges.empty()) {
		return nullptr;
	}

	return std::move(this->movesAndJokerChanges.front().first);
}

std::unique_ptr<JokerChange> RPSFilePlayerAlgorithm::getJokerChange() {
	if (this->movesAndJokerChanges.empty()) {
		return nullptr;
	}

	return std::move(this->movesAndJokerChanges.front().second);
}

void RPSFilePlayerAlgorithm::notifyFightResult(const FightInfo &fightInfo) {
	if (fightInfo.getWinner()) {} // To get rid of warnings...
}

void RPSFilePlayerAlgorithm::notifyOnInitialBoard(const Board &b, const std::vector<std::unique_ptr<FightInfo>> &fights) {
	if (b.getPlayer(RPSPoint(1, 1)) || fights.empty()) {} // Again, no warnings
}

void RPSFilePlayerAlgorithm::notifyOnOpponentMove(const Move &move) {
	if (move.getTo().getY()) {} // Yay, no warnings!
}