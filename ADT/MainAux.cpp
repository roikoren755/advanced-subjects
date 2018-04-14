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
	ifstream file;
	file.open(positionFile);

	std::string command;
	RPS_Message message;
	int i = 1;
	int ret = 0;
	if (file.is_open()) {
		while (!ret && std::getline(file, command)) {
			RPSCommand rpsCommand;
			rpsCommand = RPSCommandFactory::getRPSCommand(command, rpsCommand);
			if (rpsCommand.getCommandType() == Position) {
				message = rpsGame.rpsSetPosition(rpsCommand, player);
				switch (message) {
					case Destination_Out_Of_Range:
						std::cout << "ERROR: " << player << "'s position file, line " << i
								  << ": Destination is out of range." << std::endl;
						ret = i;
						break;
					case Bad_Position:
						std::cout << "ERROR: " << player << "'s position file, line " << i
								  << ": Destination already contains a player piece." << std::endl;
						ret = i;
						break;
					case Success:
						break;
					default:
						std::cout << "ERROR: " << player << "'s position file, line " << i
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
		ret = rpsGame.rpsValidateNumberOfJokers(player) ? ret : -2;
	}
	else {
		ret = -1;
	}

	return ret;
}

int MainAux::rpsPlayTwoPlayerMoves(RPSGame &rpsGame, std::string &player1MoveFile, std::string &player2MoveFile) {
	ifstream player1File;
	player1File.open(player1MoveFile);
	ifstream player2File;
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
