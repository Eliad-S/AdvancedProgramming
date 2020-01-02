//
// Created by shirgold and EliadSellem on 26/12/2019.
//

#ifndef ADVANCEDPROGRAMMING_OPENCONTROLCOMMAND_H
#define ADVANCEDPROGRAMMING_OPENCONTROLCOMMAND_H


#include "Command.h"

class OpenControlCommand : public Command {
    /*
     * open a new connection with the simulator as a client and update
     * him values that have been change in our data.
     */
    virtual int execute(int index);

public:
    condition_variable cv;
    mutex m;
};

#endif //ADVANCEDPROGRAMMING_OPENCONTROLCOMMAND_H
