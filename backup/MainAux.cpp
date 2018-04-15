//
// Created by Roi Koren on 09/04/2018.
//

#include <iostream>
#include <fstream>
#include "MainAux.h"
#include "RPSCommandFactory.h"

RPS_Message rpsSetMoveFromFile(RPSGame &rpsGame, RPSCommand &rpsCommand, int player, int line) {
	RPS_Message message = rpsGame.rpsSetMove(rpsCommand, player);
	switch (message) {
		case Invalid_Argument:
			std::cout << "ERROR: " << player << "'s move file, line " << line << ": Badly formatted move." << std::endl;
			break;
		case Destination_Out_Of_Range:
			std::cout << "ERROR: " << player << "'s move file, line " << line << ": Destination is out of range."
																		<< std::endl;
			break;
		case Source_Out_Of_Range:
			std::cout << "ERROR: " << player << "'s position file, line " << line
					  << ": Starting position is out of range." << std::endl;
			break;
		case Illegal_Move:
			std::cout << "ERROR: " << player << "'s position file, line " << line
					  << ": Piece cannot move to a non-adjacent position." << std::endl;
			break;
		case No_Piece_In_Position:
			std::cout << "ERROR: " << player << "'s position file, line " << line
					  << ": Position does not contain a piece." << std::endl;
			break;
		case Immovable_Piece_In_Position:
			std::cout << "ERROR: " << player << "'s position file, line " << line
					  << ": Piece at given position is an immovable one." << std::endl;
			break;
		case No_Joker_in_position:
			std::cout << "ERROR: " << player << "'s position file, line " << line
					  << ": Position does not contain a joker piece." << std::endl;
			break;
		case Invalid_Joker_Assigning:
			std::cout << "ERROR: " << player << "'s position file, line " << line
					  << ": Joker can not become that piece!." << std::endl;
			break;
		case No_Winner:
		case All_Flags_Captured:
		case All_Moving_Pieces_Captured:
			break;
		default:
			std::cout << "ERROR: " << player << "'s position file, line " << line
					  << ": An unknown error has occurred." << std::endl;
			break;
	}

	return message;
}

int MainAux::rpsLoadPositionFile(RPSGame &rpsGame, std::string &positionFile, int player) {
	std::ifstream file;
	file.open(positionFile);

	std::string command;
	RPS_Message message;
	bool valid = true;
	int i = 1;
	int ret = 0;
	if (file.is_open()) {
		while (!ret && std::getline(file, command)) {
			RPSCommand rpsCommand;
			rpsCommand = RPSCommandFactory::getRPSCommand(command, rpsCommand);
		//	std::cout<<rpsCommand.getPieceType()<<":"<<rpsCommand.getToX()<<","<<rpsCommand.getToY()<<std::endl;
			if (rpsCommand.getCommandType() == Position) {
				message = rpsGame.rpsSetPosition(rpsCommand, player);
				//std::cout<<message<<std::endl;
				switch (message) {
					case Destination_Out_Of_Range:
						std::cout << "ERROR: player  " << player << "'s position file, line " << i
								  << ": Destination is out of range." << std::endl;
						valid = false;
						ret = i;
						break;
					case Bad_Position:
						std::cout << "ERROR: player " << player << "'s position file, line " << i
								  << ": Destination already contains a player piece." << std::endl;
						valid = false;
						ret = i;
						break;
					case Too_Many_Pieces:
						std::cout << "ERROR: player " << player << "'s position file, line " << i
								  << ": Illegal number of pieces of type "<<rpsCommand.getPieceType() << std::endl;
						ret = i;
						valid = false;
						break;
					case Success:
						break;
					default:
						std::cout << "ERROR: player " << player << "'s position file, line " << i
								  << ": An unknown error has occurred." << std::endl;
						ret = i;
						break;
				}
			}
			else {
				std::cout << "ERROR: " << player << "'s position file, line " << i
						  << ": Line isn't a legal positioning command." << std::endl;
			}

			i++;
		}

		file.close();

		if(valid && !rpsGame.rpsValidateNumberOfJokers(player)){
			std::cout << "ERROR: Player "<<player<<" hadn't placed all of his flags." << std::endl;
			ret = i;
			valid = false;
		}
		//ret = rpsGame.rpsValidateNumberOfJokers(player) ? ret : -2;
	}
	else {
		ret = -1;
	}

	if(valid){
		return 0;
	}

	return ret;
}

int MainAux::rpsPlayTwoPlayerMoves(RPSGame &rpsGame, std::string &player1MoveFile, std::string &player2MoveFile) {
	std::ifstream player1File;
	player1File.open(player1MoveFile);
	std::ifstream player2File;
	player2File.open(player2MoveFile);

	int finished = 0;
	bool player1Finished = false;
	bool player2Finished = false;
	int player1Line = 1;
	int player2Line = 1;
	RPS_Message message;
	std::string command;
	if (player1File.is_open() && player2File.is_open()) {
		while (!finished && (!player1Finished || !player2Finished)) {
			if (!player1Finished && std::getline(player1File, command)) {
				RPSCommand rpsCommand;
				rpsCommand = RPSCommandFactory::getRPSCommand(command, rpsCommand);
				message = rpsSetMoveFromFile(rpsGame, rpsCommand, 1, player1Line);
				switch (message) {
					case No_Winner:
						player1Line++;
						break;
					case All_Moving_Pieces_Captured:
					case All_Flags_Captured:
						player1Finished = true;
						player2Finished = true;
						finished = -2;
						break;
					default:
						rpsGame.rpsSetWinner(2);
						player1Finished = true;
						player2Finished = true;
						finished = player1Line;
						break;
				}
			}
			else {
				player1Finished = true;
			}

			if (!player2Finished && std::getline(player2File, command)) {
				RPSCommand rpsCommand;
				rpsCommand = RPSCommandFactory::getRPSCommand(command, rpsCommand);
				message = rpsSetMoveFromFile(rpsGame, rpsCommand, 2, player2Line);
				switch (message) {
					case No_Winner:
						player2Line++;
						break;
					case All_Moving_Pieces_Captured:
					case All_Flags_Captured:
						player1Finished = true;
						player2Finished = true;
						finished = -3;
						break;
					default:
						rpsGame.rpsSetWinner(1);
						player1Finished = true;
						player2Finished = true;
						finished = player1Line;
						break;
				}
			}
			else {
				player2Finished = true;
			}
		}
	}
	else {
		finished = -1;
	}

	return finished;
}

int MainAux::rpsPrintGamePositionErrorResult(RPSGame &rpsGame,int player1lineError,int player2lineError){
	std::ofstream fout("rps.output");

	int winner;
	if(player1lineError&&player2lineError){
		winner = 0;
	}
	else{
		winner = player1lineError? 2 : 1;
	}
	fout<<"Winner: "<<winner<<std::endl;

	if(winner == 0){
		fout<<"Reason: "<<"Bad Positioning input file for both players - player 1: line "<<player1lineError
				<<", player 2: line "<<player2lineError<<std::endl;
	}
	else{
		int loser = player1lineError? 1 : 2;
		int errorLine = player1lineError? player1lineError : player2lineError;
		fout<<"Bad Positioning input file for player "<< loser
				<<" - line "<<errorLine<< std::endl;
	}
	fout<<std::endl;
	fout<<rpsGame;

	return 1;
}






