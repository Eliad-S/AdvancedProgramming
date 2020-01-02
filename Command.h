//
// Created by shirgold and EliadSellem on 25/12/2019.
//

#ifndef ADVANCED__COMMANDS_H_
#define ADVANCED__COMMANDS_H_

#include <sys/socket.h>
#include <unordered_map>
#include "Obj.h"
#include <unistd.h>
#include <netinet/in.h>
#include <thread>
#include <arpa/inet.h>
#include <condition_variable>
#include <vector>
#include <iostream>
#include <cstring>
#include <map>
#include <regex>
#include "ex1.h"
using namespace std;
class Command {
public:

    virtual int execute(int index) = 0;
/*
 * The function recieve a STObjMap and and expresion, calculate it and return the value.
 */
    float calculateExpression(unordered_map<string, Obj *> &STObjMap, const string &e);
// distructor.
    virtual ~Command() {}
/*
 * return the commandMap from the singleton class "InterpreterFlight"
 */
    unordered_map<string, Command *> &getCommandMap();
/*
 * return the STSimulatorMap from the singleton class "InterpreterFlight"
 */
    unordered_map<string, Obj *> &getSTSimulatorMap();
/*
 * return the vector "array" from the singleton class "InterpreterFlight"
 */
    vector<string> &getArray();
/*
 * return the STObjMap from the singleton class "InterpreterFlight"
 */
    unordered_map<string, Obj *> &getSTObjMap();

};


#endif //ADVANCED__COMMANDS_H_