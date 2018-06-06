//
// Created by Roi Koren on 30/04/2018.
//
#ifndef ADVANCED_SUBJECTS_RPSFIGHTINFO_H
#define ADVANCED_SUBJECTS_RPSFIGHTINFO_H

#include "FightInfo.h"
#include "RPSPoint.h"

class RPSFightInfo: public FightInfo {
	const RPSPoint position;
	const char player1piece;
	const char player2piece;
	const int winner;
public:
	RPSFightInfo(Point& position, char player1piece, char player2piece, int winner): position(position),
																					   player1piece(player1piece),
																					   player2piece(player2piece),
																					   winner(winner) {}
	RPSFightInfo(int x, int y, char player1piece, char player2piece, int winner): position(RPSPoint(x, y)),
																					 player1piece(player1piece),
																					 player2piece(player2piece),
																					 winner(winner) {}
	RPSFightInfo(FightInfo&& fightInfo): position(fightInfo.getPosition()), player1piece(fightInfo.getPiece(1)),
										 player2piece(fightInfo.getPiece(2)), winner(fightInfo.getWinner()) {}
	RPSFightInfo(const FightInfo& fightInfo): position(fightInfo.getPosition()), player1piece(fightInfo.getPiece(1)),
									   player2piece(fightInfo.getPiece(1)), winner(fightInfo.getWinner()) {}
	const RPSPoint& getPosition() const override { return this->position; }
	char getPiece(int player) const override { return player == 1 ? player1piece : (player == 2 ? player2piece : '#'); }
	int getWinner() const override { return this->winner; }
	~RPSFightInfo() override = default;
};

#endif //ADVANCED_SUBJECTS_RPSFIGHTINFO_H
