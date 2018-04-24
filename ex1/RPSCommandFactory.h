//
// Created by Roi Koren on 08/04/2018.
//

#ifndef ADVANCED_SUBJECTS_RPSCOMMANDFACTORY_H
#define ADVANCED_SUBJECTS_RPSCOMMANDFACTORY_H

#include "RPSCommand.h"
#include <string.h>


class RPSCommandFactory {
public:
    static RPSCommand* getRPSCommand(char const* command);
};

#endif //ADVANCED_SUBJECTS_RPSCOMMANDFACTORY_H
