//
// Created by shirgold on 30/12/2019.
//
#include "NewFuncCommand.h"
#include "InterpreterFlight.h"
int NewFuncCommand:: execute(int index){
    vector<string> newArray;
    string functionName = getArray()[index + 1];
    string varName = getArray()[index + 3];
    newArray.push_back(varName);
    index += 5;
    int start = index;
    int jump = 5;
    int counter = 1;
    while (counter != 0) {
        if(getArray()[index] == "}") {
            counter--;
        }
        if(getArray()[index] == "{") {
            counter++;
        }

        if(counter != 0) {
            newArray.push_back(getArray()[index]);
        }
        index++;
        jump++;
    }
    Parser* parser = new Parser(start,index-1, getArray());
    InterpreterFlight::getInstance()->getFunctionMap()[functionName] = {varName,parser};
    return jump;

}
