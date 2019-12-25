//
// Created by shirgold on 25/12/2019.
//

#ifndef ADVANCEDPROGRAMMING_WHILECOMMAND_H
#define ADVANCEDPROGRAMMING_WHILECOMMAND_H


#include "conditionParser.h"

class WhileCommand : public ConditionParser {
    virtual int execute(int index);
};

#endif //ADVANCEDPROGRAMMING_WHILECOMMAND_H
