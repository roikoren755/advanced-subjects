//
// Created by Roi Koren on 08/04/2018.
//

#include "RPSCommandFactory.h"

int main() {
	RPSCommand* command = RPSCommandFactory::getRPSCommand("1 3 4 5 J: 78 12839 B");
	std::cout << (command->getCommandType() == Move ? "true" : "false") << endl;
}