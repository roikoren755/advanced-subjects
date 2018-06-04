//
// Created by Roi Koren on 04/06/2018.
//

#ifndef ADVANCED_SUBJECTS_TOURNAMENTMANAGER_H
#define ADVANCED_SUBJECTS_TOURNAMENTMANAGER_H

#include <string>
#include <functional>
#include "PlayerAlgorithm.h"

class TournamentManager {
public:
	static TournamentManager getTournamentManager() {
		return TournamentManager();
	}
	void registerAlgorithm(std::string id, std::function<std::unique_ptr<PlayerAlgorithm>()> factoryMethod) {}
};

#endif //ADVANCED_SUBJECTS_TOURNAMENTMANAGER_H
