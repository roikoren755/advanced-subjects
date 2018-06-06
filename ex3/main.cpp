//
// Created by user on 01/05/2018.
//

#include <iostream>
#include <string.h>
#include "MainAux.h"

#define THREADS_OPTION "-threads"
#define PATH_OPTION "-path"

int main(int argc, char* argv[]) {
    if (argc > 5 || !(argc % 2)) {
        std::cout << "USAGE: ./ex3 [-threads <num_of_threads>] [-path <location_of_algorithms>]" << std::endl;
        return 0;
    }

    int threads = 0;
    std::string path;
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
                if (path.empty()) {
                    path = argv[i + 1];
                }

                else {
                    std::cout << "USAGE: ./ex3 [-threads <num_of_threads>] [-path <location_of_algorithms>]" << std::endl;
                    return 0;
                }
            }
        }
    }

    return 0;
}