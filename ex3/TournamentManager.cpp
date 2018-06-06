//
// Created by Roi Koren on 04/06/2018.
//

#include <iostream>
#include <random>
#include "TournamentManager.h"

TournamentManager TournamentManager::tournamentManager;

TournamentManager& TournamentManager::getTournamentManager() {
	return TournamentManager::tournamentManager;
}

void TournamentManager::registerAlgorithm(std::string id,
										  std::function<std::unique_ptr<PlayerAlgorithm>()> factoryMethod) {
	auto iterator = this->id2factory.find(id);
	if (iterator != this->id2factory.end()) {
		std::cout << "WARNING: tried loading " << id << " more than once. Only the last version will be saved." << std::endl;
	}
	id2factory[id] = factoryMethod;
}

void TournamentManager::printTournamentResult() {
	std::map<int, std::string> sortedScore;

	for (auto it = score.begin(); it != score.end(); it++) {
		sortedScore[it->second] = it->first;
	}

	for (auto it = sortedScore.rbegin(); it != sortedScore.rend(); it++) {
		std::cout << it->second << " " << it->first<< std::endl;
	}
}

void TournamentManager::initializeGamesList() {
	unsigned long numberOfPlayers = this->id2factory.size();
	std::vector<std::string> players;
	for (auto it = this->id2factory.begin(); it != this->id2factory.end(); it++) {
		players.push_back((*it).first);
	}

	std::vector<int> gamesLeftToPlay(numberOfPlayers);
	for (unsigned long i = 0; i < numberOfPlayers; i++) {
		gamesLeftToPlay.at(i) = 30;
	}

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(0, 29);

	unsigned long opponent;
	for (unsigned long i = 0; i < numberOfPlayers; i++) {
		while (gamesLeftToPlay.at(i) > 0) {
			opponent = (unsigned long) dist(mt);
			if (opponent != i) {
				gamesLeftToPlay.at(i)--;
				gamesLeftToPlay.at(opponent)--;
				this->gamesToPlay.emplace_back(std::make_tuple(players.at(i), players.at(opponent)));
			}
		}
	}
}
