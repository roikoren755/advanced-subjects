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
    if (argc > 5 || !(argc % 2)) {
        std::cout << "USAGE: ./ex3 [-threads <num_of_threads>] [-path <location_of_algorithms>]" << std::endl;
        return 0;
    }

    int threads = 0;
    std::string path = "./";
    if (argc > 1) {
        for (int i = 1; i < argc; i += 2) {
            if (!strcmp(argv[i], THREADS_OPTION)) {
                if (!threads) {
                    threads = MainAux::GetPositiveInt(argv[i + 1]);
                    if (!threads) {
                        std::cout << "USAGE: ./ex3 [-threads <num_of_threads>] [-path <location_of_algorithms>]" << std::endl;
                        return 0;
                    }
                }
                else {
                    std::cout << "USAGE: ./ex3 [-threads <num_of_threads>] [-path <location_of_algorithms>]" << std::endl;
                    return 0;
                }
            }

            else if (!strcmp(argv[i], PATH_OPTION)) {
                if (path == "./") {
                    path = argv[i + 1];
                }

                else {
                    std::cout << "USAGE: ./ex3 [-threads <num_of_threads>] [-path <location_of_algorithms>]" << std::endl;
                    return 0;
                }
            }
        }
    }

    if (path.back() != '/') {
        path.append("/");
    }

    int numOfPlayers = TournamentManager::getTournamentManager().loadAlgorithms(path);
    if (numOfPlayers < 0) {
        return numOfPlayers;
    }
    else if (numOfPlayers < 2) {
        std::cout << numOfPlayers << std::endl;
        std::cout << "USAGE: location of algorithms does not contain enough players" << std::endl;
        return 0;
    }

    return 0;
}
