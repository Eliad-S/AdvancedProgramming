//
// Created by eliadsellem on 12/10/19.
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

using namespace std;
class Command {

 public:
    condition_variable cv;
  virtual int execute(vector<string> &array, int index, unordered_map<string, Obj *> &STSimulatorMap,
                      unordered_map<string, Obj *> &STObjMap,
                      unordered_map<string, Command*> &commandMap) = 0;

  float calculateExpression(unordered_map<string, Obj *> &STObjMap,  const string& e);
  virtual ~Command() {}
};

class openDataCommand : public Command {
  virtual int execute(vector<string> &array, int index, unordered_map<string, Obj *> &STSimulatorMap,
                      unordered_map<string, Obj *> &STObjMap,
                      unordered_map<string, Command*> &commandMap);
};

class openControlCommand : public Command {
  virtual int execute(vector<string> &array, int index, unordered_map<string, Obj *> &STSimulatorMap,
                      unordered_map<string, Obj *> &STObjMap,
                      unordered_map<string, Command*> &commandMap);
};

class varCommand : public Command {
  virtual int execute(vector<string> &array, int index, unordered_map<string, Obj *> &STSimulatorMap,
                      unordered_map<string, Obj *> &STObjMap,
                      unordered_map<string, Command*> &commandMap);
};

class objCommand : public Command {
  virtual int execute(vector<string> &array, int index, unordered_map<string, Obj *> &STSimulatorMap,
                      unordered_map<string, Obj *> &STObjMap,
                      unordered_map<string, Command*> &commandMap);
};

class conditionParser : public Command {
  public:
  vector<Command *> commands;
};

class ifCommand : public Command {
  virtual int execute(vector<string> &array, int index, unordered_map<string, Obj *> &STSimulatorMap,
                      unordered_map<string, Obj *> &STObjMap,
                      unordered_map<string, Command*> &commandMap);
};

class whileCommand : public Command {
  virtual int execute(vector<string> &array, int index, unordered_map<string, Obj *> &STSimulatorMap,
                      unordered_map<string, Obj *> &STObjMap,
                      unordered_map<string, Command*> &commandMap);
};
class printCommand : public Command {
  virtual int execute(vector<string> &array, int index, unordered_map<string, Obj *> &STSimulatorMap,
                      unordered_map<string, Obj *> &STObjMap,
                      unordered_map<string, Command*> &commandMap);
};
class sleepCommand : public Command {
  virtual int execute(vector<string> &array, int index, unordered_map<string, Obj *> &STSimulatorMap,
                      unordered_map<string, Obj *> &STObjMap,
                      unordered_map<string, Command*> &commandMap);
};
#endif //ADVANCED__COMMANDS_H_