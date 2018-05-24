//
// Created by user on 21/05/2018.
//



#include <string.h>
#include <fstream>
#include <memory>
#include "RPSAutomaticPlayerAlgorithm.h"
#include "RPSFilePlayerAlgorithm.h"
#include "MainAux.h"
#include "RPSGame.h"


#define AUTO "auto"
#define FILE "file"
#define TOKENS "-vs"
#define PLAYER1_POSITION_FILE "player1.rps_board"
#define PLAYER2_POSITION_FILE "player2.rps_board"
#define PLAYER1_MOVES_FILE "player1.rps_moves"
#define PLAYER2_MOVES_FILE "player2.rps_moves"

#define ALL_FLAGS_CAPTURED -2
#define ALL_MOVING_PIECES_CAPTURED -3
#define LEGAL_TIE 0
#define ILLEGAL_MOVE 1


#define BOTH_PLAYERS_LOST 3

int MainAux::RPSMakePlayerAlgorithm( char arg[],std::vector<unique_ptr<PlayerAlgorithm>>& algorithms){
    char* players[NUM_PLAYERS];
    players[PLAYER(1)] = strtok(arg,TOKENS);
    players[PLAYER(2)] = strtok(NULL,TOKENS);

    for(int i = 0; i<NUM_PLAYERS; i++){
        if(strcpy(players[i],AUTO)) {
            unique_ptr<PlayerAlgorithm> ptr = std::make_unique<PlayerAlgorithm>(new RPSAutomaticPlayerAlgorithm());
            algorithms.push_back(std::move(ptr));
        }
        else if(strcpy(players[i],FILE)) {
            unique_ptr<PlayerAlgorithm> ptr = std::make_unique<PlayerAlgorithm>(new RPSFilePlayerAlgorithm(
                    i+1,(i+1 == 1)?PLAYER1_POSITION_FILE:PLAYER2_POSITION_FILE,
                        (i+1 == 1)?PLAYER1_MOVES_FILE:PLAYER2_MOVES_FILE));
            algorithms.push_back(std::move(ptr));
        }
        else{
            std::cout<<"ERROR: bad command line argument"<<std::endl;
            return i+1;
        }
        return SUCCESS;
    }
}

int MainAux::RPSPerformPositioning(RPSGame game ,std::vector<unique_ptr<PlayerAlgorithm>>& algorithms) {
    std::vector<unique_ptr<PiecePosition>> playerPos;
    RPS_Message message;
    int ret = 0;

    for (int i = 0; i < NUM_PLAYERS; i++) {
        algorithms[i]->getInitialPositions(i + 1, playerPos);
        for (auto& ptr : playerPos) {
            message = game.setPosition(*ptr, i + 1);
            switch (message) {
                case Destination_Out_Of_Range:
                    std::cout << "ERROR: player  " << i + 1 << "'s positioning:"
                                                               " Destination is out of range." << std::endl;
                    ret += (i + 1);
                    break;
                case Bad_Position:
                    std::cout << "ERROR: player " << i + 1 << "'s positioning:"
                                                              " Destination already contains a player piece."
                              << std::endl;
                    ret += (i + 1);
                    break;
                case Too_Many_Pieces:
                    std::cout << "ERROR: player " << i + 1 << "'s positioning:"
                                                              " Illegal number of pieces of type " <<
                              (*ptr).getPiece() << std::endl;
                    ret += (i + 1);
                    break;
                case Invalid_Argument:
                    std::cout << "ERROR: player " << i + 1 << "'s positioning:"
                                                              "An invalid position command" << std::endl;
                    ret += (i + 1);
                    break;
                case Success:
                    break;
                default:
                    std::cout << "ERROR: player " << i + 1 << "'s positioning:"
                                                              " An unknown error has occurred." << std::endl;
                    break;
            }
        }

        if (!game.validateNumberOfFlags(i + 1)) {
            std::cout << "ERROR: Player " << i + 1 << " hadn't placed all of his flags." << std::endl;
        }

    }
    return ret;
}


//==================================================================================


int MainAux::RPSPrintGamePositionErrorResult(RPSGame game, int feedback){
    std::ofstream fout("rps.output");
    if (!fout.is_open()) {
        std::cout << "ERROR: could'nt open output file" << std::endl;
        return -1;
    }

    int winner;
    if (feedback == BOTH_PLAYERS_LOST) {
        winner = 0;
    }
    else {
        winner = (feedback == 1 ) ? 2 : 1;
    }

    fout << "Winner: " << winner << std::endl;

    if (!winner) {
        fout << "Reason: " << "Bad Positioning for both players" << std::endl;
    }
    else {
        int loser = feedback;
        fout << "Bad Positioning for player " << loser << std::endl;
    }

    fout << std::endl;
    fout << game;

    fout.close();
    return 1;
}
//==========================================================================



int MainAux::RPSPlayTwoPlayersMoves(RPSGame& game, std::vector<unique_ptr<PlayerAlgorithm>>& algorithms){
    int winner;
    RPS_Message message;
    int moveCounter = 0;

    while(!winner){
        for (int i = 0; i < NUM_PLAYERS; i++) {
            auto movePtr = algorithms[i]->getMove();
           // Move move = *movePtr;
            int toX = movePtr->getTo().getX();
            int toY = movePtr->getTo().getY();
            message = game.setMove(std::move(movePtr),i+1);
            if(message == Success || message == Battle_Required){
                game.setNewJoker(std::move(algorithms[i]->getJokerChange()));
                algorithms[1-i]->notifyOnOpponentMove(*movePtr);
                if(message == Battle_Required) {
                    FightInfo info = game.performBattle(toX, toY);
                    algorithms[1-1]->notifyFightResult(info);
                    algorithms[2-1]->notifyFightResult(info);
                }
            }
            else{  //in this case illegal move was done
                winner = (i+1==1)? 2 : 1;
                game.setWinner(winner);
                return ILLEGAL_MOVE;
            }

            message = game.checkWinner();
        }
    }
}




//==========================================================================


int MainAux::RPSPrintGameResult(RPSGame &game, int reason) {
    std::ofstream fout("rps.output");
    if (!fout.is_open()) {
        std::cout << "ERROR: could'nt open output file" << std::endl;
        return -1;
    }

    int winner = game.getWinner();
    fout << "Winner: " << winner << std::endl;
    fout << "Reason: ";
    switch (reason) {
            case ALL_FLAGS_CAPTURED:
                if (winner) {
                    fout << "All flags of the opponent are captured" << std::endl;
                }
                else {
                    fout << "A tie - all flags are eaten by both players in the position files" << std::endl;
                }
                break;
            case ALL_MOVING_PIECES_CAPTURED:
                if (winner) {
                    fout << "All moving PIECEs of the opponent are eaten" << std::endl;
                }
                else {
                    fout << "A tie - All moving PIECEs of the opponent are eaten" << std::endl; // TODO - Both players have no moving pieces after positioning tie message
                }
                break;
            case LEGAL_TIE:
                fout << "A tie - both Moves input files done without a winner" << std::endl;
                break;
            case ILLEGAL_MOVE:
                int loser = (winner == 1)? 2 : 1;
                fout << "Bad Move for player " << loser <<std::endl;
                break;
            default:
                break;
        }


    fout << std::endl;
    fout << game;

    fout.close();
    return 1;
}