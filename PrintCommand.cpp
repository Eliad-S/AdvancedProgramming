//
// Created by shirgold and EliadSellem on 26/12/2019.
//

#include "PrintCommand.h"
int PrintCommand::execute(int index) {
    string print = getArray()[index + 1];
    auto obj = getSTObjMap().find(print);
    // in the map
    if (obj != getSTObjMap().end()) {
        cout << obj->second->getValue() << endl;
    // message
    } else if (print.find("\"") < print.length()) {
        print = print.substr(1);
        print = print.substr(0, print.find("\""));
        cout << print << endl;
    // expression
    } else {
        int value = calculateExpression(getSTObjMap(), print);
        cout << value << endl;
    }
    return 2;
}