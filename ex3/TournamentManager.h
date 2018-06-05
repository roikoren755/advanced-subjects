//
// Created by Roi Koren on 04/06/2018.
//

#ifndef ADVANCED_SUBJECTS_TOURNAMENTMANAGER_H
#define ADVANCED_SUBJECTS_TOURNAMENTMANAGER_H

#include <string>
#include <functional>
#include <map>
#include "PlayerAlgorithm.h"

class TournamentManager {
	static TournamentManager tournamentManager;
	std::map<std::string, std::function<std::unique_ptr<PlayerAlgorithm>()>> id2factory;
	std::map<std::string,int> score;

	TournamentManager() = default;
public:
	TournamentManager(const TournamentManager& tournamentManager) = delete;
	TournamentManager operator=(const TournamentManager& tournamentManager) = delete;
	static TournamentManager& getTournamentManager();
	void registerAlgorithm(std::string id, std::function<std::unique_ptr<PlayerAlgorithm>()> factoryMethod);
	void printTournamentResult();
};

#endif //ADVANCED_SUBJECTS_TOURNAMENTMANAGER_H
