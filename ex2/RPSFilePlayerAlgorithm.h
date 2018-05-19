//
// Created by user on 04/05/2018.
//


#ifndef ADVANCED_SUBJECTS_RPSFILEPLAYERALGORITHM_H
#define ADVANCED_SUBJECTS_RPSFILEPLAYERALGORITHM_H

#include "PlayerAlgorithm.h"
#include "RPSPiecePosition.h"
#include "RPSMove.h"
#include "RPSJokerChange.h"
#include "RPSFightInfo.h"
#include "RPSBoard.h"

#define PLAYER1_MOVES_FILE "player1.rps_moves"
#define PLAYER2_MOVES_FILE "player2.rps_moves"

class RPSFilePlayerAlgorithm : public PlayerAlgorithm {
    int player;
    std::vector<unique_ptr<PiecePosition>> initialPositions;
    std::vector<std::pair<unique_ptr<Move>, unique_ptr<JokerChange>>> movesAndJokerChanges;
    unsigned long turn = 0;

public:
    RPSFilePlayerAlgorithm(int player, const std::string& initialPositionsFile, const std::string& movesFile);
    void getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill) override;
	void notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights) override;
    void notifyOnOpponentMove(const Move& move) override;
    void notifyFightResult(const FightInfo& fightInfo) override;
    unique_ptr<Move> getMove() override;
    unique_ptr<JokerChange> getJokerChange() override; // nullptr if no change is requested
    ~RPSFilePlayerAlgorithm() override = default;

private:
    void loadInitialPositionsFromFile(const std::string& initialPositionsFile);
    void loadMovesAndJokerChangesFromFile(const std::string& movesAndJokerChangesFile);
};

#endif //ADVANCED_SUBJECTS_RPSFILEPLAYERALGORITHM_H
