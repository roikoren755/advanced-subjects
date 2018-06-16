//
// Created by user on 01/05/2018.
//
#include <iostream>
#include <cstring>
#include "MainAux.h"
#include "TournamentManager.h"

#define THREADS_OPTION "-threads"
#define PATH_OPTION "-path"

int main(int argc, char* argv[]) {
    if (argc > 5 || !(argc % 2)) { // Check number of arguments
        std::cout << "USAGE: ./ex3 [-threads <num_of_threads>] [-path <location_of_algorithms>]" << std::endl;
        return 0;
    }

    int threads = -1;
    std::string path = "./";
    bool pathProvided = false;
    if (argc > 1) {
        for (int i = 1; i < argc; i += 2) {
            if (!strcmp(argv[i], THREADS_OPTION)) { // Threads argument provided
                if (threads == -1) {
                    threads = MainAux::GetPositiveInt(argv[i + 1]);
                    if (!threads) { // But is illegal!
                        std::cout << "USAGE: number of threads must be a positive integer" << std::endl;
                        return 0;
                    }
                }
                else { // Threads argument already provided
                    std::cout << "USAGE: ./ex3 [-threads <num_of_threads>] [-path <location_of_algorithms>]" << std::endl;
                    return 0;
                }
            }

            else if (!strcmp(argv[i], PATH_OPTION)) { // Path argument provided
                if (!pathProvided) {
                    path = argv[i + 1];
                    pathProvided = true;
                }

                else { // Path argument already provided
                    std::cout << "USAGE: ./ex3 [-threads <num_of_threads>] [-path <location_of_algorithms>]" << std::endl;
                    return 0;
                }
            }
        }
    }

    if (path.back() != '/') { // Normalize path
        path.append("/");
    }

    if (threads == -1) { // Default number of threads to run
        threads = 4;
    }

    int numOfPlayers = TournamentManager::getTournamentManager().loadAlgorithms(path); // Load algorithms
    if (numOfPlayers < 0) { // Error loading
        return numOfPlayers;
    }
    else if (numOfPlayers < 2) { // Not enough players!
        std::cout << "USAGE: location of algorithms does not contain enough players" << std::endl;
        return 0;
    }

    TournamentManager::getTournamentManager().initializeGamesList(); // Decide which games to player
    TournamentManager::getTournamentManager().runTournament(threads); // Play
    TournamentManager::getTournamentManager().printTournamentResult(); // Declare winner

    return 0;
}
