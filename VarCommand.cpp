//
// Created by shirgold and EliadSellem on 26/12/2019.
//
#include "VarCommand.h"
#include "InterpreterFlight.h"

int VarCommand::execute(int index) {
    string varName = getArray()[index + 1];
    string flashOrEqual = getArray()[index + 2];
    string simOrExpression = getArray()[index + 3];
    Obj *obj;

    //var name ->/<- sim
    if (simOrExpression == "sim") {
        int flag = 0;
        string sim = getArray()[index + 4];
        unordered_map<string, Obj *>::iterator it;
        //check if the obj exist in STSimulatorMap.
        for (it = getSTSimulatorMap().begin(); it != getSTSimulatorMap().end(); it++) {
            obj = it->second;
            if (obj->getSim() == sim) {
                flag = 1;
                break;
            }
        }
        if (flashOrEqual == "->") {
            if (flag == 1) {
                obj->setDirection(1);
                obj->setName(varName);
            } else {
                obj = new Obj(varName, sim, 1);
            }
        } else {
            if (flag == 1) {
                obj->setDirection(-1);
                obj->setName(varName);
            } else {
                obj = new Obj(varName, sim, -1);
            }
        }
        InterpreterFlight::getInstance()->setSTObjMap(varName, obj);
        return 5;
    } else {

        if (flashOrEqual == "=") {
            float value = 0;
            string expression = getArray()[index + 3];
            value = calculateExpression(getSTObjMap(), expression);
            //cout << "succeed calculating " << endl;
            obj = new Obj(varName, value);
            InterpreterFlight::getInstance()->setSTObjMap(varName, obj);

        }
        return 4;
    }
}