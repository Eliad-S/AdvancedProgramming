//
// Created by shirgold and EliadSellem on 26/12/2019.
//

#include "conditionParser.h"
bool ConditionParser::checkCondition1(string var) {
  //calculate the expression and return if true if its > 0.
  float val = calculateExpression(getSTObjMap(), var);
  if (val) {
    return true;
  }
  return false;
}

bool ConditionParser::checkCondition2(string var1, string condition, string var2) {
  bool flag = false;
  //caclulate both expression and return true if they implement the logic with the operator given
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
