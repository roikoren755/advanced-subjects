//
// Created by Roi Koren on 08/04/2018.
//

#ifndef ADVANCED_SUBJECTS_RPSCOMMANDFACTORY_H
#define ADVANCED_SUBJECTS_RPSCOMMANDFACTORY_H

#include "RPSCommand.h"

class RPSCommandFactory {
public:
	static RPSCommand& getRPSCommand(const std::string &command, RPSCommand& rpsCommand);
};

#endif //ADVANCED_SUBJECTS_RPSCOMMANDFACTORY_H
