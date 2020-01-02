//
// Created by shirgold and EliadSellem on 26/12/2019.
//

#ifndef ADVANCEDPROGRAMMING_FUNCCOMMAND_H
#define ADVANCEDPROGRAMMING_FUNCCOMMAND_H


#include "Command.h"
#include "InterpreterFlight.h"

class FuncCommand : public Command {
    /*
     * execute all the commands in the function.
     */
    virtual int execute(int index);

};


#endif //ADVANCEDPROGRAMMING_FUNCCOMMAND_H
