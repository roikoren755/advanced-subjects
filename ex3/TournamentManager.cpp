//
// Created by Roi Koren on 04/06/2018.
//

#include <iostream>
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