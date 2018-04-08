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

RPSCommand* RPSCommandFactory::getRPSCommand(char const* command) {
    char buffer[MAXIMUM_COMMAND_LENGTH + 1];
    if (!strcpy(buffer, command)) {
        return NULL;
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
        return NULL;
    }

    if (argument[0] > 'A' && argument[0] < 'Z' && !argument[1]) {
        if (argument[0] == 'J') {
            jokerInvolved = true;
        }
        commandType = Position;

        if ((pieceType = charToPieceType(argument[0])) == InvalidPiece) {
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

    return new RPSCommand(commandType, pieceType, fromX, fromY, toX, toY, jokerInvolved, jokerX, jokerY);
}