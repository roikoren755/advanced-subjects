//
// Created by Roi Koren on 20/05/2018.
//

#ifndef ADVANCED_SUBJECTS_RPSAUTOMATICPLAYERALGORITHM_H
#define ADVANCED_SUBJECTS_RPSAUTOMATICPLAYERALGORITHM_H

#include "PlayerAlgorithm.h"
#include "RPSBoard.h"


class RPSAutomaticPlayerAlgorithm: public PlayerAlgorithm {
	RPSBoard board;
	int player = 0;
	int opponent = 0;
	int opponentFlags = 0;
	int opponentBombs = 0;
	int opponentJokers = 0;
	int opponentRocks = 0;
	int opponentPapers = 0;
	int opponentScissors = 0;
public:
    RPSAutomaticPlayerAlgorithm();
	RPSAutomaticPlayerAlgorithm(int flags, int bombs, int jokers, int rocks, int papers, int scissors):
			opponentFlags(flags), opponentBombs(bombs), opponentJokers(jokers), opponentRocks(rocks),
			opponentPapers(papers), opponentScissors(scissors) {}
	void getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill) override;
	void notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights) override;
	void notifyOnOpponentMove(const Move& move) override; // called only on opponent’s move
	void notifyFightResult(const FightInfo& fightInfo) override; // called only if there was a fight
	unique_ptr<Move> getMove() override;
	unique_ptr<JokerChange> getJokerChange() override; // nullptr if no change is requested
	~RPSAutomaticPlayerAlgorithm() override = default;
private:
	void updateBoardByBattle(const FightInfo& fightInfo);
};

#endif //ADVANCED_SUBJECTS_RPSAUTOMATICPLAYERALGORITHM_H
