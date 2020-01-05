//
// Created by shirgold and EliadSellem on 26/12/2019.
//

#include "FuncCommand.h"

int FuncCommand:: execute(int index){
  //the name of the function
    string name = getArray()[index + 1];
    vector<string> array;
    //the value of the argument to the function
    string value = getArray()[index + 2];

    unordered_map<string, pair<string ,Parser *>>::iterator it =
            InterpreterFlight::getInstance()->getFunctionMap().find(name);
    //the argument name in the declaration of the function "x" for example.
    string var = it->second.first;
    //calculate the expression of the argument given
    float f = calculateExpression(getSTObjMap(),value);
    // create a temporery obj with the name "x" of the declaration and the value as the argument given
    Obj* obj = new Obj(var,f);
    getSTObjMap()[var] = obj;
    Parser* parser = it->second.second;
    parser->interpret();
    //delete the temporery obj.
    delete(getSTObjMap().find(var)->second);
    getSTObjMap().erase(getSTObjMap().find(var));
    return 3;
}
