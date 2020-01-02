//
// Created by shirgold and EliadSellem on 25/12/2019.
//

#include "ObjCommand.h"
#include "InterpreterFlight.h"

int ObjCommand::execute(int index) {

    string name = getArray()[index + 1];
    string expression = getArray()[index + 3];
    float value = calculateExpression(getSTObjMap(), expression);
    unordered_map<string, Obj *>::iterator it = getSTObjMap().find(name);
    it->second->setValue(value);
    if (it->second->getDirection() == 1) {
        it->second->setValueChanged(true);
        InterpreterFlight::getInstance()->pushQueue(it->second);
        InterpreterFlight::getInstance()->controlCommand->cv.notify_one();
    }
    return 4;
}