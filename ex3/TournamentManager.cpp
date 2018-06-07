//
// Created by Roi Koren on 04/06/2018.
//
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

void TournamentManager::tournamentRunGame(std::string plr1, std::pair<std::string,bool> plr2){
    unique_ptr<PlayerAlgorithm> player1 = this->id2factory[plr1]();
    unique_ptr<PlayerAlgorithm> player2 = this->id2factory[plr2.first]();

    int winner = MainAux::runGame(std::move(player1),std::move(player2));
    switch (winner){
        case  1:
			score_mutex.lock();
			score[plr1]+=3;
			score_mutex.unlock();
            break;
        case 2:
			score_mutex.lock();
			if(plr2.second){
                score[plr2.first]+=3;
            }
			score_mutex.unlock();
			break;
        case 0:
			score_mutex.lock();
			score[plr1]+=1;
			if(plr2.second){
				score[plr2.first]+=1;
			}
			score_mutex.unlock();
		default:
			break;
	}
}

void TournamentManager::managerThreadWork(){

	while (true){

		games_list_mutex.lock();
		if(gamesToPlay.empty()){
			games_list_mutex.unlock();
			break;
		}
		else{
			auto curGame = gamesToPlay.back();
			gamesToPlay.pop_back();
			games_list_mutex.unlock();

			tournamentRunGame(curGame.first, curGame.second );
		}

	}
}

void TournamentManager::runTournament(int n_threads) {
	std::vector<std::thread> threads(n_threads - 1);
	for (auto it = threads.begin(); it != threads.end(); it++) {
		*it = std::thread(managerThreadWork);
	}
	managerThreadWork(); //main thread also has to do work

	for (auto it = threads.begin(); it != threads.end(); it++) {
		(*it).join();  //safety, threads should be done by here
	}
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
