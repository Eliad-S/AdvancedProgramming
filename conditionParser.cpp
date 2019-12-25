//
// Created by shirgold on 25/12/2019.
//

#include "conditionParser.h"
bool ConditionParser::checkCondition1(string var) {
    float val = calculateExpression(getSTObjMap(), var);
    if (val) {
        return true;
    }
    return false;
}

bool ConditionParser::checkCondition2(string var1, string condition, string var2) {
    bool flag = false;
    float val1 = calculateExpression(getSTObjMap(), var1);
    float val2 = calculateExpression(getSTObjMap(), var2);
    if (condition == "!=") {
        flag = (val1 != val2);
    }
    if (condition == "==") {
        flag = (val1 == val2);
    }
    if (condition == ">=") {
        flag = (val1 >= val2);
    }
    if (condition == "<=") {
        flag = (val1 <= val2);
    }
    if (condition == ">") {
        flag = (val1 > val2);
    }
    if (condition == "<") {
        flag = (val1 < val2);
    }
    return flag;
}
