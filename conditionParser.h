//
// Created by shirgold on 25/12/2019.
//

#ifndef ADVANCEDPROGRAMMING_CONDITIONPARSER_H
#define ADVANCEDPROGRAMMING_CONDITIONPARSER_H


#include "Command.h"

class ConditionParser : public Command {
public:
    vector<Command *> commands;
    bool checkCondition1(string var);
    bool checkCondition2(string var1, string condition, string var2);
};


#endif //ADVANCEDPROGRAMMING_CONDITIONPARSER_H
