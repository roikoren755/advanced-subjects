cmake_minimum_required(VERSION 3.10)
project(advanced-subjects)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra \ -Werror -pedantic-errors -DNDEBUG")
set(SOURCE_FILES ex2/main.cpp ex2/RPSGame.h ex2/RPSGame.cpp ex2/RPSPiece.h ex2/RPSPiece.cpp ex2/FightInfo.h ex2/JokerChange.h ex2/Move.h ex2/PiecePosition.h ex2/PlayerAlgorithm.h ex2/Point.h ex2/RPSPoint.h ex2/RPSBoard.h ex2/RPSBoard.cpp ex2/RPSFightInfo.h ex2/RPSMove.h ex2/RPSPiecePosition.h ex2/RPSFilePlayerAlgorithm.cpp ex2/RPSJokerChange.h ex2/RPSAutomaticPlayerAlgorithm.h ex2/RPSAutomaticPlayerAlgorithm.cpp)
add_executable(dbsg ${SOURCE_FILES})