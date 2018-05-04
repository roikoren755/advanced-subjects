//
// Created by user on 04/05/2018.
//

#ifndef ADVANCED_SUBJECTS_RPSFILEPLAYERALGORITHM_H
#define ADVANCED_SUBJECTS_RPSFILEPLAYERALGORITHM_H

#define PLAYER1_MOVES_FILE "player1.rps_moves"
#define PLAYER2_MOVES_FILE "player2.rps_moves"

class RPSFilePlayerAlgorithm : public PlayerAlgorithm{
    int player;
    //std::ifstream positionFile;
    std::ifstream movesFile;


public:
    RPSFilePlayerAlgorithm(int player): player(player),
                    movesFile(player==1?PLAYER1_MOVES_FILE:PLAYER2_MOVES_FILE){}

     void getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill) override ;
     void notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights) override ;
     void notifyOnOpponentMove(const Move& move); // called only on opponent's move
     void notifyFightResult(const FightInfo& fightInfo); // called only if there was a fight
     unique_ptr<Move> getMove();
     unique_ptr<JokerChange> getJokerChange(); // nullptr if no change is requested
     ~PlayerAlgorithm() {}


};



#endif //ADVANCED_SUBJECTS_RPSFILEPLAYERALGORITHM_H
