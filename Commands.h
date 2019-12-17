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
#include <map>
#include "InterpreterFlight.h"
#include <regex>


using namespace std;
class Command {

 public:
    condition_variable cv;
  virtual int execute(int index) = 0;

  float calculateExpression(unordered_map<string, Obj *> &STObjMap,  const string& e);
  virtual ~Command() {}
};

class openDataCommand : public Command {
  virtual int execute(int index);

//  void setSimulatorDetails(char &buffer, valRead);
};

class openControlCommand : public Command {
  virtual int execute(int index);
};

class varCommand : public Command {
  virtual int execute(int index);
};

class objCommand : public Command {
  virtual int execute(int index);
};

class conditionParser : public Command {
  public:
  vector<Command *> commands;
  bool checkCondition1(string var,
                         unordered_map<string, Obj *> &STObjMap);
  bool checkCondition2(string var1, string condition, string var2,
                         unordered_map<string, Obj *> &STObjMap);
};

class ifCommand : public conditionParser {
  virtual int execute(int index);
};

class whileCommand : public conditionParser {
  virtual int execute(int index);
};

class printCommand : public Command {
  virtual int execute(int index);
};

class sleepCommand : public Command {
  virtual int execute(int index);
};
#endif //ADVANCED__COMMANDS_H_