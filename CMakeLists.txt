cmake_minimum_required(VERSION 3.10)
project(advanced-subjects)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra \ -Werror -pedantic-errors -DNDEBUG")
set(SOURCE_FILES ex3/main.cpp ex3/MainAux.cpp ex3/MainAux.h ex3/RPSGame.h ex3/RPSGame.cpp ex3/RPSPiece.h ex3/RPSPiece.cpp ex3/FightInfo.h ex3/JokerChange.h ex3/Move.h ex3/PiecePosition.h ex3/PlayerAlgorithm.h ex3/Point.h ex3/RPSPoint.h ex3/RPSBoard.h ex3/RPSBoard.cpp ex3/RPSFightInfo.h ex3/RPSMove.h ex3/RPSPiecePosition.h ex3/RPSJokerChange.h ex3/RSPPlayer_204057566.h ex3/RSPPlayer_204057566.cpp ex3/AlgorithmRegistration.h ex3/AlgorithmRegistration.cpp ex3/TournamentManager.cpp ex3/TournamentManager.h)
add_executable(dbsg ${SOURCE_FILES})