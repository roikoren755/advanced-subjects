//
// Created by user on 21/05/2018.
//
#include <fstream>
#include <cstring>
#include "RSPPlayer_204057566.h"
#include "MainAux.h"
#include "RPSGame.h"
#include "RPSMove.h"

#define MAX_NO_FIGHT_MOVES_ALLOWED 100
#define ALL_FLAGS_CAPTURED (-2)
#define ALL_MOVING_PIECES_CAPTURED (-3)
#define LEGAL_TIE 0
#define ILLEGAL_MOVE 1
#define BOTH_PLAYERS_LOST 3
#define PLAYER(i) ((i) - 1)

int MainAux::runGame(unique_ptr<PlayerAlgorithm> player1, unique_ptr<PlayerAlgorithm> player2) {
    std::vector<unique_ptr<PlayerAlgorithm>> algorithms;
    algorithms.push_back(std::move(player1));
    algorithms.push_back(std::move(player2));

    RPSGame game = RPSGame();
    int feedback = MainAux::RPSPerformPositioning(game, algorithms);
    if (feedback == BOTH_PLAYERS_LOST) {
        return 0;
    }
    else if (feedback > 0) { // if feedback == 0 game not done
        return feedback == 1 ? 2 : 1;
    }

    std::vector<unique_ptr<FightInfo>> fights;

    feedback = game.finishPositioningStage(fights);
    if (feedback) { // game is done
        return game.getWinner();
    }

    algorithms[PLAYER(1)]->notifyOnInitialBoard(game.getBoard(), fights);
    algorithms[PLAYER(2)]->notifyOnInitialBoard(game.getBoard(), fights);

    RPSPlayTwoPlayersMoves(game, algorithms);
    return game.getWinner();
}

int MainAux::GetPositiveInt(const char *const integer) {
    int result = 0;
    int i = 0;
    while (integer && integer[i] >= '0' && integer[i] <= '9') {
        result *= 10;
        result += integer[i] - '0';
        i++;
    }

    return result;
}

int MainAux::RPSPerformPositioning(RPSGame& game ,std::vector<unique_ptr<PlayerAlgorithm>>& algorithms) {
    std::vector<unique_ptr<PiecePosition>> playerPos;
    RPS_Message message;
    int ret = 0;
    int valid = 1;

    for (int i = 0; i < NUM_PLAYERS; i++) {
        algorithms[i]->getInitialPositions(i + 1, playerPos);
        for (auto& ptr : playerPos) {
            if(ptr == nullptr){
                ret += (i + 1);
                valid = 0;
                break;
            }
            message = game.setPosition(*ptr, i + 1);
            if (message != Success) {
                ret += (i + 1);
            }

            if (ret > 0) {
                valid = 0;
                break;
            }

        }

        if (valid && !game.validateNumberOfFlags(i + 1)) {
            ret += (i + 1);
        }

        playerPos.clear();

    }

    return ret;
}

//==================================================================================
// TODO - do we need that?
int MainAux::RPSPrintGamePositionErrorResult(RPSGame& game, int feedback) {

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
        winner = feedback == 1 ? 2 : 1;
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
int MainAux::RPSPlayTwoPlayersMoves(RPSGame& game, std::vector<unique_ptr<PlayerAlgorithm>>& algorithms) {
    //int winner;
    RPS_Message message;
    int moveCounter = 0;
    bool player1Finished = false;
    bool player2Finished = false;

    while (!player1Finished || !player2Finished) {
        for (int i = 0; i < NUM_PLAYERS; i++) {
            if (i == 1 ? player1Finished : player2Finished) {
                continue;
            }
            auto movePtr = algorithms[i]->getMove();
            if (movePtr == nullptr) {
                i == 1 ? (player1Finished = true) : (player2Finished = true);

                moveCounter++;
                if (moveCounter >= MAX_NO_FIGHT_MOVES_ALLOWED) {
                    game.setWinner(0);
                    return LEGAL_TIE;
                }

                break;
            }

            RPSMove move = *movePtr;
            int toX = movePtr->getTo().getX();
            int toY = movePtr->getTo().getY();
            message = game.setMove(move, i + 1);
            if (message == Battle_Required || message == Success) {
				algorithms[1 - i]->notifyOnOpponentMove(move);

				if (message == Battle_Required) {
					RPSFightInfo info = game.performBattle(toX, toY);
					algorithms[1 - 1]->notifyFightResult(info);
					algorithms[2 - 1]->notifyFightResult(info);

					message = game.checkWinner();
					switch (message) {
						case No_Winner:
							break;
						case All_Moving_Pieces_Captured:
							return ALL_MOVING_PIECES_CAPTURED;
						case All_Flags_Captured:
							return ALL_FLAGS_CAPTURED;
						default: // shouldn't happen
							break;
					}
				}
				else {
					moveCounter++;
					if (moveCounter >= MAX_NO_FIGHT_MOVES_ALLOWED) {
						game.setWinner(0);
						return LEGAL_TIE;
					}
				}

				if (game.changeJokerRepresentation(algorithms[i]->getJokerChange()) != Success) {
					game.setWinner(i + 1 == 1 ? 2 : 1);
					std::cout<<"illegal move for player "<<i+1<<std::endl;
					return ILLEGAL_MOVE;
				}
            }
            else {  // in this case illegal move was done
				game.setWinner(i + 1 == 1 ? 2 : 1);
				return ILLEGAL_MOVE;
			}

            message = game.checkWinner();
            switch (message) {
                case No_Winner:
                    break;
                case All_Moving_Pieces_Captured:
                    return ALL_MOVING_PIECES_CAPTURED;
                case All_Flags_Captured:
                    return ALL_FLAGS_CAPTURED;
                default: // shouldn't happen
                    break;
            }
        }
    }

    return LEGAL_TIE;
}

//==========================================================================
//TODO do we need that?
int MainAux::RPSPrintGameResult(RPSGame& game, int reason) {
    std::ofstream fout("rps.output");
    if (!fout.is_open()) {
        std::cout << "ERROR: could'nt open output file" << std::endl;
        return -1;
    }

    int winner = game.getWinner();
    int loser = winner == 1 ? 2 : 1;

    fout << "Winner: " << winner << std::endl;
    fout << "Reason: ";
    switch (reason) {
            case ALL_FLAGS_CAPTURED:
                if (winner) {
                    fout << "All flags of the opponent are captured" << std::endl;
                }
                else {
                    fout << "A tie - all flags are eaten by both players in the position stage" << std::endl;
                }
                break;
            case ALL_MOVING_PIECES_CAPTURED:
                if (winner) {
                    fout << "All moving PIECEs of the opponent are eaten" << std::endl;
                }
                else {
                    // TODO - Both players have no moving pieces after positioning tie message
                    fout << "A tie - All moving PIECEs of the opponent are eaten" << std::endl;
                }
                break;
            case LEGAL_TIE:
                fout << "A tie - max no-fight moves allowed performed " << std::endl;
                break;
            case ILLEGAL_MOVE:
                fout << "Bad Move for player " << loser << std::endl;
                break;
            default:
                break;
        }

    fout << std::endl;
    fout << game;

    fout.close();

    return 1;
}
