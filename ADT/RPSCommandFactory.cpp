//
// Created by Roi Koren on 08/04/2018.
//

#include "RPSCommandFactory.h"

#define DELIMITERS " \t\n\r"

PieceType charToPieceType(char piece) {
	switch (piece) {
		case 'R':
			return Rock;
		case 'P':
			return Paper;
		case 'S':
			return Scissors;
		case 'B':
			return Bomb;
		case 'F':
			return Flag;
		default:
			return InvalidPiece;
	}
}

int getPositiveInt(char* integer) {
	int result = 0;
	int i = 0;
	while (integer && integer[i] >= '0' && integer[i] <= '9') {
		result *= 10;
		result += integer[i] - '0';
		i++;
	}

	return result;
}

RPSCommand& RPSCommandFactory::getRPSCommand(const std::string& command, RPSCommand &rpsCommand) {
	char buffer[MAXIMUM_COMMAND_LENGTH + 1];
	if (!strcpy(buffer, command.c_str())) {
		rpsCommand.setCommandType(InvalidCommand);
		return rpsCommand;
	}

	CommandType commandType = InvalidCommand;
	PieceType pieceType = InvalidPiece;
	int fromX = 0;
	int fromY = 0;
	int toX = 0;
	int toY = 0;
	bool jokerInvolved = false;
	int jokerY = 0;
	int jokerX = 0;

	char* argument = strtok(buffer, DELIMITERS);
	if (!argument) {
		rpsCommand.setCommandType(NoLine);
		return rpsCommand;
	}

	if (argument[0] > 'A' && argument[0] < 'Z' && !argument[1]) {
		commandType = Position;
		if (argument[0] == 'J') {
			jokerInvolved = true;
		}
		else if ((pieceType = charToPieceType(argument[0])) == InvalidPiece) {
			commandType = InvalidCommand;
		}

		argument = strtok(NULL, DELIMITERS);
		if (!argument || (toX = getPositiveInt(argument)) < 1) {
			commandType = InvalidCommand;
		}

		argument = strtok(NULL, DELIMITERS);
		if (!argument || (toY = getPositiveInt(argument)) < 1) {
			commandType = InvalidCommand;
		}

		if (jokerInvolved) {
			argument = strtok(NULL, DELIMITERS);
			if (!argument || (pieceType = charToPieceType(argument[0])) == InvalidPiece || argument[1]) {
				commandType = InvalidCommand;
			}
		}
	}

	else if (argument[0] > '0' && argument[0] <= '9') {
		commandType = Move;
		if ((fromX = getPositiveInt(argument)) < 1) {
			commandType = InvalidCommand;
		}

		argument = strtok(NULL, DELIMITERS);
		if (!argument || (fromY = getPositiveInt(argument)) < 1) {
			commandType = InvalidCommand;
		}

		argument = strtok(NULL, DELIMITERS);
		if (!argument || (toX = getPositiveInt(argument)) < 1) {
			commandType = InvalidCommand;
		}

		argument = strtok(NULL, DELIMITERS);
		if (!argument || (toY = getPositiveInt(argument)) < 1) {
			commandType = InvalidCommand;
		}

		argument = strtok(NULL, DELIMITERS);
		if (argument) {
			if (!strcmp(argument, "J:")) {
				jokerInvolved = true;
				argument = strtok(NULL, DELIMITERS);
				if (!argument || (jokerX = getPositiveInt(argument)) < 1) {
					commandType = InvalidCommand;
				}

				argument = strtok(NULL, DELIMITERS);
				if (!argument || (jokerY = getPositiveInt(argument)) < 1) {
					commandType = InvalidCommand;
				}

				argument = strtok(NULL, DELIMITERS);
				if (!argument || (pieceType = charToPieceType(argument[0])) == InvalidPiece || argument[1]) {
					commandType = InvalidCommand;
				}
			}
		}
	}

	if ((argument = strtok(NULL, DELIMITERS))) {
		commandType = InvalidCommand;
	}

	rpsCommand.setCommandType(commandType);
	rpsCommand.setPieceType(pieceType);
	rpsCommand.setFromX(fromX);
	rpsCommand.setFromY(fromY);
	rpsCommand.setToX(toX);
	rpsCommand.setToY(toY);
	rpsCommand.setJokerInvolved(jokerInvolved);
	rpsCommand.setJokerX(jokerX);
	rpsCommand.setJokerY(jokerY);

//	std::cout << "Position ?" << (commandType == Position) << "Joker ?" << jokerInvolved << std::endl;
	return rpsCommand;
}