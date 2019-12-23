//
// Created by eliadsellem on 12/11/19.
//

#ifndef ADVANCED__INTERPRETERFLIGHT_H_
#define ADVANCED__INTERPRETERFLIGHT_H_

#include <vector>
#include <fstream>
#include <unordered_map>
#include "Commands.h"

using namespace std;

class InterpreterFlight {
  unordered_map<string, Command *> commandMap;
  unordered_map<string, Obj *> STSimulatorMap;
  unordered_map<string, Obj *> STObjMap;
  vector<string> array;
  queue<string> simToUpdate;
  static InterpreterFlight *instance;
  bool keepOpenServerThread;
  bool keepOpenClientThread;
  string sims[36];

  InterpreterFlight() {
    this->commandMap = unordered_map<string, Command *>();
    this->STSimulatorMap = unordered_map<string, Obj *>();
    this->STObjMap = unordered_map<string, Obj *>();
    setCommandMap(this->commandMap);
    setSTSimulatorMap(this->STSimulatorMap);
    this->keepOpenServerThread = true;
    this->keepOpenClientThread = true;
    setSimArray();
  }

 public:
  mutex mutex_;
  mutex queueLock;
  thread clientThread;
  thread serverThread;
  static InterpreterFlight *getInstance() {
    if (!instance)
      instance = new InterpreterFlight();
    return instance;
  }

  unordered_map<string, Command *> &get_CommandMap();

  unordered_map<string, Obj *> &get_STSimulatorMap();

  unordered_map<string, Obj *> &get_STObjMap();

  vector<string> &get_Array();

  void setCommandMap(unordered_map<string, Command *> &map);

  void setSTSimulatorMap(unordered_map<string, Obj *> &map);

  void setTokens(vector<string> &tokens);

  void parser();

  bool getKeepOpenServerThread();

  bool getKeepOpenClientThread();
  void setSTObjMap(string basic_string, Obj *p_obj);

  void setSimArray();
  string getIndexOfArray(int index);
  Obj* get_STSimulatorObjBySim(string sim);

  void pushQueue(Obj *obj);
  queue<string> getQueue();
};

#endif //ADVANCED__INTERPRETERFLIGHT_H_
