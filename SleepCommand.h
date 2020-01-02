//
// Created by shirgold and EliadSellem on 26/12/2019.
//
#ifndef ADVANCEDPROGRAMMING_SLEEPCOMMAND_H
#define ADVANCEDPROGRAMMING_SLEEPCOMMAND_H


#include "Command.h"

class SleepCommand : public Command {
    /*
     * sleep the program.
     */
    virtual int execute(int index);
};


#endif //ADVANCEDPROGRAMMING_SLEEPCOMMAND_H
