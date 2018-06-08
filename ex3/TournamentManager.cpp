//
// Created by Roi Koren on 04/06/2018.
//
#include <algorithm>
#include <iostream>
#include <random>
#include <dirent.h>
#include <thread>
#include <dlfcn.h>
#include "TournamentManager.h"
#include "MainAux.h"

TournamentManager TournamentManager::tournamentManager;

TournamentManager& TournamentManager::getTournamentManager() {
	return TournamentManager::tournamentManager;
}

//============================================================
void TournamentManager::tournamentRunGame(std::string player1Name, std::pair<std::string,bool> player2Name) {
    int winner = MainAux::runGame(this->id2factory[player1Name](), this->id2factory[player2Name.first]());
    switch (winner) {
        case 1:
			scoreMutex.lock();
			score[player1Name] += 3;
			scoreMutex.unlock();
            break;
        case 2:
			if (player2Name.second) {
				scoreMutex.lock();
                score[player2Name.first] += 3;
				scoreMutex.unlock();
            }
			break;
        case 0:
			scoreMutex.lock();
			score[player1Name] += 1;
			if (player2Name.second) {
				score[player2Name.first] += 1;
			}
			scoreMutex.unlock();
		default: // Shouldn't get here
			break;
	}
}

void TournamentManager::managerThreadWork() {
	while (!this->gamesToPlay.empty()) {
		this->gamesListMutex.lock();
		auto curGame = this->gamesToPlay.back();
		this->gamesToPlay.pop_back();
		this->gamesListMutex.unlock();
		this->tournamentRunGame(curGame.first, curGame.second);
	}
}

void TournamentManager::runTournament(int numberOfThreads) {
	//initialize score to 0
	for(auto player : this->id2factory){
		this->score[player.first] = 0;
	}

	if (numberOfThreads == 1) {
		this->managerThreadWork();
		return;
	}

	std::vector<std::thread> threads((unsigned long) numberOfThreads - 1);
	for (auto& thread: threads) {
		thread = std::thread(&TournamentManager::managerThreadWork, this);
	}

	managerThreadWork(); // main thread can also do work

	for (auto& thread: threads) {
		thread.join(); // safety, threads should be done by here
	}
}

void TournamentManager::registerAlgorithm(std::string id, std::function<std::unique_ptr<PlayerAlgorithm>()>& factoryMethod) {
	auto iterator = this->id2factory.find(id);
	if (iterator != this->id2factory.end()) {
		std::cout << "WARNING: tried loading " << id << " more than once. Only the last version will be saved." << std::endl;
	}
	id2factory[id] = std::move(factoryMethod);
}

void TournamentManager::printTournamentResult() {
	std::vector<std::pair<std::string, int>> sortedScore;

	for (const auto& playerAndScore: this->score) {
		sortedScore.emplace_back(std::make_pair(playerAndScore.first, playerAndScore.second));
	}

	std::sort(sortedScore.begin(), sortedScore.end(), [=](std::pair<std::string, int>& a, std::pair<std::string, int>& b) {
	                                                    return a.second > b.second; });

	for (const auto& playerAndScore: sortedScore) {
		std::cout << playerAndScore.first << " " << playerAndScore.second << std::endl;
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
				this->gamesToPlay.emplace_back(std::make_pair(players.at(i), std::make_pair(players.at(opponent), true)));
				tries = 0;
			}
			else {
				tries++;
			}

			if (tries > 10 && opponent != i) {
				tries = 0;
				gamesLeftToPlay.at(i)--;
				gamesLeftToPlay.at(opponent)--;
				this->gamesToPlay.emplace_back(std::make_pair(players.at(i), std::make_pair(players.at(opponent), false)));
			}
		}
	}
}

int TournamentManager::loadAlgorithms(const std::string& pathToDir) {
	DIR *dir;
	struct dirent *ent;
	int nameLength;
	if ((dir = opendir(pathToDir.c_str())) != nullptr) {
		while ((ent = readdir(dir)) != nullptr) {
			nameLength = 0;
			while (ent->d_name[nameLength]) {
				nameLength++;
			}
			if (nameLength > 3 && ent->d_name[nameLength - 1] == 'o' && ent->d_name[nameLength - 2] == 's' &&
				ent->d_name[nameLength - 3] == '.') {
				void* soHandle = dlopen((pathToDir + ent->d_name).c_str(), RTLD_LAZY);
				if (!soHandle) {
					std::cout << "ERROR: Could not open " << dlerror() << std::endl;
					closedir(dir);
					return -1;
				}
				this->soHandles.push_back(soHandle);
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
	this->score.clear();
	this->gamesToPlay.clear();
	this->id2factory.clear();
	if (!this->soHandles.empty()) {
		for (auto handle: this->soHandles) {
			dlclose(handle);
		}
	}
}
