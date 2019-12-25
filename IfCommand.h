//
// Created by shirgold on 25/12/2019.
//

#ifndef ADVANCEDPROGRAMMING_IFCOMMAND_H
#define ADVANCEDPROGRAMMING_IFCOMMAND_H


#include "conditionParser.h"

class IfCommand : public ConditionParser {
    virtual int execute(int index);
};


#endif //ADVANCEDPROGRAMMING_IFCOMMAND_H
