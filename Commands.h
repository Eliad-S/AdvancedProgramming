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

using namespace std;
class Command {

 public:
  virtual int execute(vector<string> &array, int index, unordered_map<string, Obj *> &STSimulatorMap,
                      unordered_map<string, Obj *> &STObjMap) = 0;
  virtual ~Command() {}
};

class openDataCommand : public Command {
  virtual int execute(vector<string> &array, int index, unordered_map<string, Obj *> &STSimulatorMap,
                      unordered_map<string, Obj *> &STObjMap);
};

class openControlCommand : public Command {
  virtual int execute(vector<string> &array, int index, unordered_map<string, Obj *> &STSimulatorMap,
                      unordered_map<string, Obj *> &STObjMap);
};

class varCommand : public Command {
  virtual int execute(vector<string> &array, int index, unordered_map<string, Obj *> &STSimulatorMap,
                      unordered_map<string, Obj *> &STObjMap);
};

class objCommand : public Command {
  virtual int execute(vector<string> &array, int index, unordered_map<string, Obj *> &STSimulatorMap,
                      unordered_map<string, Obj *> &STObjMap);
};

class conditionParser : public Command {
  virtual int execute(vector<string> &array, int index, unordered_map<string, Obj *> &STSimulatorMap,
                      unordered_map<string, Obj *> &STObjMap);
};

class ifCommand : public Command {
  virtual int execute(vector<string> &array, int index, unordered_map<string, Obj *> &STSimulatorMap,
                      unordered_map<string, Obj *> &STObjMap);
};

class whileCommand : public Command {
  virtual int execute(vector<string> &array, int index, unordered_map<string, Obj *> &STSimulatorMap,
                      unordered_map<string, Obj *> &STObjMap);
};
class printCommand : public Command {
  virtual int execute(vector<string> &array, int index, unordered_map<string, Obj *> &STSimulatorMap,
                      unordered_map<string, Obj *> &STObjMap);
};
class sleepCommand : public Command {
  virtual int execute(vector<string> &array, int index, unordered_map<string, Obj *> &STSimulatorMap,
                      unordered_map<string, Obj *> &STObjMap);
};
#endif //ADVANCED__COMMANDS_H_