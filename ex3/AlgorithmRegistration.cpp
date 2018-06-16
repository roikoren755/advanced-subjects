//
// Created by Roi Koren on 04/06/2018.
//
#include "AlgorithmRegistration.h"
#include "TournamentManager.h"

AlgorithmRegistration::AlgorithmRegistration(std::string id,
											 std::function<std::unique_ptr<PlayerAlgorithm>()> factoryMethod) {
	TournamentManager::getTournamentManager().registerAlgorithm(id, factoryMethod);
}
