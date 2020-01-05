//
// Created by shirgold and EliadSellem on 26/12/2019.
//
#include "NewFuncCommand.h"
#include "InterpreterFlight.h"
int NewFuncCommand:: execute(int index){
    vector<string> newArray;
    //function name
    string functionName = getArray()[index + 1];
    //var name
    string varName = getArray()[index + 3];
    newArray.push_back(varName);
    index += 5;
    int start = index;
    int jump = 5;
    int counter = 1;
    //indentify the scop range.
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
    //create a new parser with the start index and the end index of the scop function
    //and add it to the functionMap with the name function as key
    Parser* parser = new Parser(start,index-1, getArray());
    InterpreterFlight::getInstance()->getFunctionMap()[functionName] = {varName,parser};
    return jump;

}
