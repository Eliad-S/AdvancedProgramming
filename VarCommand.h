//
// Created by shirgold and EliadSellem on 26/12/2019.
//

#ifndef ADVANCEDPROGRAMMING_VARCOMMAND_H
#define ADVANCEDPROGRAMMING_VARCOMMAND_H

#include "Command.h"

class VarCommand : public Command {
    /*
     * insert new variable to the map.
     */
    virtual int execute(int index);
};


#endif //ADVANCEDPROGRAMMING_VARCOMMAND_H
