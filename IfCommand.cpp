//
// Created by shirgold and EliadSellem on 26/12/2019.
//
#include "IfCommand.h"
int IfCommand::execute(int index) {
    bool flag;
    int counter;
    string v1 = getArray()[index + 1];
    string v2 = getArray()[index + 2];
    if (v2 == "{") {
        counter = 3;
        flag = checkCondition1(v1);
    } else {
        counter = 5;
        string v3 = getArray()[index + 3];
        flag = checkCondition2(v1, v2, v3);
    }
    if (!flag) {
        while (getArray()[index + counter] != "}") {
            counter++;
        }
        return counter;
    } else {
        while (getArray()[index + counter] != "}") {
            Command *c = getCommandMap().find(getArray()[index + counter])->second;
            counter += c->execute(index + counter);
        }
    }
    return counter;
}