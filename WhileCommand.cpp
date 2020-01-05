//
// Created by shirgold and EliadSellem on 26/12/2019.
//

#include "WhileCommand.h"
#include "Parser.h"

int WhileCommand::execute(int index) {
    bool flag;
    int counter1;
    int counter2;
    int whichCondition;
    //first expression.
    string v1 = getArray()[index + 1];
    //second expression, can be an operator in case of binary bool expression or "{" if unary bool expression
    string v2 = getArray()[index + 2];
    string v3;
    //in case of unary
    if (v2 == "{") {
        counter1 = 3;
        flag = checkCondition1(v1);
        whichCondition = 1;
    //in case of binary
    } else {
        counter1 = 4;
        v3 = getArray()[index + 3];
        flag = checkCondition2(v1, v2, v3);
        whichCondition = 2;
    }
    counter2 = counter1;
    while (getArray()[index + counter2] != "}") {
        counter2++;
    }
    counter2++;
    if (!flag) {
        return counter2;
    }
    //the condition is an unary bool expression.
    if (whichCondition == 1) {
      //while the condition is true
      while (checkCondition1(v1)) {
            counter1 = 3;
            while (getArray()[index + counter1] != "}") {
                Command *c = getCommandMap().find(getArray()[index + counter1])->second;
                counter1 += c->execute(index + counter1);
            }
        }
      //the condition is an binary bool expression.
    } else {
      //while the condition is true

      while (checkCondition2(v1, v2, v3)) {
            counter1 = 5;
            while (getArray()[index + counter1] != "}") {
                Command *c = getCommandMap().find(getArray()[index + counter1])->second;
                counter1 += c->execute(index + counter1);
            }
        }
    }
    return counter2;
}
