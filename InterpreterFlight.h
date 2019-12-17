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
  unordered_map<string, Command*> commandMap;
  map<string, Obj*> STSimulatorMap;
  unordered_map<string, Obj*> STObjMap;
  vector<string> array;
  static InterpreterFlight* instance;
  bool serverThread;

  InterpreterFlight() {
    this->commandMap =unordered_map<string, Command*>();
    this->STSimulatorMap = map<string, Obj*>();
    this->STObjMap = unordered_map<string, Obj*>();
    setCommandMap(this->commandMap);
    setSTSimulatorMap(this->STSimulatorMap);
    this->serverThread = true;
  }
public:


  static InterpreterFlight *getInstance() {
    if (!instance)
      instance = new InterpreterFlight();
    return instance;
  }
  unordered_map<string, Command*>& get_CommandMap();
  map<string, Obj*>& get_STSimulatorMap();
  unordered_map<string, Obj*>& get_STObjMap();
  vector<string>& get_Array();

  void setCommandMap(unordered_map<string, Command*> &map);
  void setSTSimulatorMap(map<string, Obj*> &map);
  void setTokens(vector<string> &tokens);
  void parser();
  bool getServer_Thread();
};

#endif //ADVANCED__INTERPRETERFLIGHT_H_
