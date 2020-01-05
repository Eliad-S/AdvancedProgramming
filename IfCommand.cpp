//
// Created by shirgold and EliadSellem on 26/12/2019.
//
#include "IfCommand.h"
int IfCommand::execute(int index) {
    bool flag;
    int counter;
    //first expression
    string v1 = getArray()[index + 1];
    //second expression.
    //can be "{" if there is an unary expression.
    string v2 = getArray()[index + 2];
    if (v2 == "{") {
        counter = 3;
        flag = checkCondition1(v1);
    } else {
        counter = 5;
        string v3 = getArray()[index + 3];
        flag = checkCondition2(v1, v2, v3);
    }
    //count all the scop of the if commands.
    if (!flag) {
        while (getArray()[index + counter] != "}") {
            counter++;
        }
        return counter;
    } else {
      //run the command until we finish the if scop.
        while (getArray()[index + counter] != "}") {
            Command *c = getCommandMap().find(getArray()[index + counter])->second;
            counter += c->execute(index + counter);
        }
    }
    return counter;
}