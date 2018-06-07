//
// Created by Roi Koren on 04/06/2018.
//
#ifndef ADVANCED_SUBJECTS_TOURNAMENTMANAGER_H
#define ADVANCED_SUBJECTS_TOURNAMENTMANAGER_H

#include <string>
#include <functional>
#include <map>
#include <vector>
#include <mutex>
#include "PlayerAlgorithm.h"

class TournamentManager {
	static TournamentManager tournamentManager;
	std::map<std::string, std::function<std::unique_ptr<PlayerAlgorithm>()>> id2factory;
	std::map<std::string,int> score;
	std::vector<std::pair<std::string, std::pair<std::string, bool>>> gamesToPlay;
	std::vector<void*> soHandles;
	std::mutex scoreMutex;
	std::mutex gamesListMutex;

	TournamentManager() = default;
	~TournamentManager();
public:
	TournamentManager(const TournamentManager& tournamentManager) = delete;
	TournamentManager operator=(const TournamentManager& tournamentManager) = delete;
	static TournamentManager& getTournamentManager();
	void tournamentRunGame(std::string player1Name, std::pair<std::string, bool> player2Name);
	void managerThreadWork();
	void runTournament(int numberOfThreads);
	void registerAlgorithm(std::string id, std::function<std::unique_ptr<PlayerAlgorithm>()>& factoryMethod);
	void printTournamentResult();
	void initializeGamesList();
	int loadAlgorithms(const std::string& pathToDir);
};

#endif //ADVANCED_SUBJECTS_TOURNAMENTMANAGER_H
