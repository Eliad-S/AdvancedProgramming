//
// Created by shirgold and EliadSellem on 26/12/2019.
//


#ifndef ADVANCEDPROGRAMMING_CONDITIONPARSER_H
#define ADVANCEDPROGRAMMING_CONDITIONPARSER_H


#include "Command.h"

class ConditionParser : public Command {
public:
    /*
     * check if the condition is true if there is only one expression.
     */
    bool checkCondition1(string var);
    /*
     * check if the condition is true if there is two expressions and condition between them.
     */
    bool checkCondition2(string var1, string condition, string var2);
};


#endif //ADVANCEDPROGRAMMING_CONDITIONPARSER_H
