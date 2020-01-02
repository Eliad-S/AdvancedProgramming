//
// Created by shirgold and EliadSellem on 26/12/2019.
//

#ifndef ADVANCEDPROGRAMMING_PRINTCOMMAND_H
#define ADVANCEDPROGRAMMING_PRINTCOMMAND_H


#include "Command.h"

class PrintCommand : public Command {
    /*
     * print the given value.
     */
    virtual int execute(int index);
};



#endif //ADVANCEDPROGRAMMING_PRINTCOMMAND_H
