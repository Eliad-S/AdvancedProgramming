//
// Created by shirgold on 25/12/2019.
//

#ifndef ADVANCEDPROGRAMMING_SLEEPCOMMAND_H
#define ADVANCEDPROGRAMMING_SLEEPCOMMAND_H


#include "Command.h"

class SleepCommand : public Command {
    virtual int execute(int index);
};


#endif //ADVANCEDPROGRAMMING_SLEEPCOMMAND_H
