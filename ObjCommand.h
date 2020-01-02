//
// Created by shirgold and EliadSellem on 26/12/2019.
//

#ifndef ADVANCEDPROGRAMMING_OBJCOMMAND_H
#define ADVANCEDPROGRAMMING_OBJCOMMAND_H


#include "Command.h"

class ObjCommand : public Command {
    virtual int execute(int index);
};



#endif //ADVANCEDPROGRAMMING_OBJCOMMAND_H
