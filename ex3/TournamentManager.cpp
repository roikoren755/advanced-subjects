//
// Created by Roi Koren on 04/06/2018.
//

#include <iostream>
#include <random>
#include <dirent.h>
#include <dlfcn.h>
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
	for (const auto& item: this->id2factory) {
		players.push_back(item.first);
	}

	std::vector<int> gamesLeftToPlay(numberOfPlayers);
	for (unsigned long i = 0; i < numberOfPlayers; i++) {
		gamesLeftToPlay.at(i) = 30;
	}

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(0, (int) numberOfPlayers - 1);

	unsigned long opponent;
	int tries = 0;
	for (unsigned long i = 0; i < numberOfPlayers; i++) {
		while (gamesLeftToPlay.at(i) > 0) {
			opponent = (unsigned long) dist(mt);
			if (opponent != i && gamesLeftToPlay.at(opponent) > 0) {
				gamesLeftToPlay.at(i)--;
				gamesLeftToPlay.at(opponent)--;
				this->gamesToPlay.emplace_back(std::make_tuple(players.at(i), std::make_tuple(players.at(opponent), true)));
				tries = 0;
			}
			else {
				tries++;
			}

			if (tries > 10 && opponent != i) {
				tries = 0;
				gamesLeftToPlay.at(i)--;
				gamesLeftToPlay.at(opponent)--;
				this->gamesToPlay.emplace_back(std::make_tuple(players.at(i), std::make_tuple(players.at(opponent), false)));
			}
		}
	}
}

int TournamentManager::loadAlgorithms(const std::string& pathToDir) {
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir(pathToDir.c_str())) != nullptr) {
		while ((ent = readdir(dir)) != nullptr) {
			if (ent->d_namlen > 3 && ent->d_name[ent->d_namlen - 1] == 'o' && ent->d_name[ent->d_namlen - 2] == 's' &&
				ent->d_name[ent->d_namlen - 3] == '.') {
				this->soHandles.emplace_back(dlopen((pathToDir + ent->d_name).c_str(), RTLD_LAZY));
			}
		}
		closedir(dir);
	}
	else {
		std::cout << "ERROR: Could not open algorithms directory" << std::endl;
		return -1;
	}

	return (int) this->soHandles.size();
}

TournamentManager::~TournamentManager() {
	for (auto handle: this->soHandles) {
		dlclose(handle);
	}
}
