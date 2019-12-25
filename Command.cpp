//
// Created by eliadsellem on 12/11/19.
//
#include "InterpreterFlight.h"
#include "ex1.h"


unordered_map<string, Command *>& Command:: getCommandMap() {
    return InterpreterFlight::getInstance()->get_CommandMap();
}

unordered_map<string, Obj *>& Command:: getSTSimulatorMap() {
    return InterpreterFlight::getInstance()->get_STSimulatorMap();
}

unordered_map<string, Obj *>& Command:: getSTObjMap() {
    return InterpreterFlight::getInstance()->get_STObjMap();
}

vector<string>& Command:: getArray() {
    return InterpreterFlight::getInstance()->get_Array();
}

float Command::calculateExpression(unordered_map<string, Obj *> &STObjMap, const string &e) {
    Interpreter *interpreter = new Interpreter(STObjMap);
    Expression *expression = nullptr;
    float result = 0;
// expression
    try {
        expression = interpreter->interpret(e);
        result = expression->calculate();
        delete expression;
        delete interpreter;
    } catch (const char *t) {
        if (expression != nullptr) {
            delete expression;
            delete interpreter;
        }
    }
    return result;
}

