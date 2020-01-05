//
// Created by shirgold and EliadSellem on 26/12/2019.
//

#include "ObjCommand.h"
#include "InterpreterFlight.h"

int ObjCommand::execute(int index) {
  //object name.
    string name = getArray()[index + 1];
    string expression = getArray()[index + 3];
    float value = calculateExpression(getSTObjMap(), expression);
    unordered_map<string, Obj *>::iterator it = getSTObjMap().find(name);
    //update the existing value withe the new value.
    it->second->setValue(value);
    //if the direction is in the simulator direction "->", push it in the queue to update
    //and notify the control command thread to update the simulator.
    if (it->second->getDirection() == 1) {
        it->second->setValueChanged(true);
        InterpreterFlight::getInstance()->pushQueue(it->second);
        InterpreterFlight::getInstance()->controlCommand->cv.notify_one();
    }
    return 4;
}