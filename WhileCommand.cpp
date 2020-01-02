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
    string v1 = getArray()[index + 1];
    string v2 = getArray()[index + 2];
    string v3;
    if (v2 == "{") {
        counter1 = 3;
        flag = checkCondition1(v1);
        whichCondition = 1;
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
    if (whichCondition == 1) {
        while (checkCondition1(v1)) {
            counter1 = 3;
            while (getArray()[index + counter1] != "}") {
                Command *c = getCommandMap().find(getArray()[index + counter1])->second;
                counter1 += c->execute(index + counter1);
            }
        }
    } else {
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

//if (whichCondition == 1) {
//counter1 = 3;
//Parser *parser = new Parser(index + counter1, counter2 - 2, getArray());
//while (checkCondition1(v1)) {
//parser->interpret();
//}
//delete (parser);
//} else {
//counter1 = 5;
//Parser *parser = new Parser(index + counter1, counter2 - 2, getArray());
//while (checkCondition2(v1, v2, v3)) {
//parser->interpret();
//}
//delete (parser);
//}