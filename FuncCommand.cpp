//
// Created by shirgold and EliadSellem on 26/12/2019.
//

#include "FuncCommand.h"

int FuncCommand:: execute(int index){
    string name = getArray()[index + 1];
    vector<string> array;
    string value = getArray()[index + 2];

    unordered_map<string, pair<string ,Parser *>>::iterator it =
            InterpreterFlight::getInstance()->getFunctionMap().find(name);
    string var = it->second.first;
    float f = calculateExpression(getSTObjMap(),value);
    Obj* obj = new Obj(var,f);
    getSTObjMap()[var] = obj;
    Parser* parser = it->second.second;
    parser->interpret();
    delete(getSTObjMap().find(var)->second);
    getSTObjMap().erase(getSTObjMap().find(var));
    delete (parser);
    return 3;
}
