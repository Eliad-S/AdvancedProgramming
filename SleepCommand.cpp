//
// Created by shirgold and EliadSellem on 26/12/2019.
//
#include "SleepCommand.h"
int SleepCommand::execute(int index) {
    int miliseconds = calculateExpression(getSTObjMap(), getArray()[index + 1]);
    this_thread::sleep_for(chrono::milliseconds(miliseconds));
    return 2;
}