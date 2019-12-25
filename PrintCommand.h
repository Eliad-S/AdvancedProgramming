//
// Created by shirgold on 25/12/2019.
//

#ifndef ADVANCEDPROGRAMMING_PRINTCOMMAND_H
#define ADVANCEDPROGRAMMING_PRINTCOMMAND_H


#include "Command.h"

class PrintCommand : public Command {
    virtual int execute(int index);
};



#endif //ADVANCEDPROGRAMMING_PRINTCOMMAND_H
