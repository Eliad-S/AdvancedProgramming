//
// Created by eliadsellem on 12/11/19.
//

#ifndef ADVANCED__INTERPRETERFLIGHT_H_
#define ADVANCED__INTERPRETERFLIGHT_H_
#include <vector>
#include <fstream>
#include <unordered_map>
#include "Commands.h"
#include "InterpreterFlight.h"



using namespace std;

class InterpreterFlight {
  unordered_map<string, Command*> commandMap;
  map<string, Obj*> STSimulatorMap;
  unordered_map<string, Obj*> STObjMap;
  vector<string> array;
  static InterpreterFlight* instance;

  InterpreterFlight(ifstream &inFile) {
    this->commandMap =unordered_map<string, Command*>();
    this->STSimulatorMap = map<string, Obj*>();
    this->STObjMap = unordered_map<string, Obj*>();
    this->array = lexer(inFile);
    setCommandMap(this->commandMap);
    setSTSimulatorMap(this->STSimulatorMap);
    inFile.close();
  }
  InterpreterFlight() {}

 public:
  static InterpreterFlight *getInstance() {
    if (!instance)
      instance = new InterpreterFlight();
    return instance;
  }
  static InterpreterFlight *getInstance(ifstream &in) {
    if (!instance)
      instance = new InterpreterFlight(in);
    return instance;
  }
  unordered_map<string, Command*>& get_CommandMap();
  map<string, Obj*>& get_STSimulatorMap();
  unordered_map<string, Obj*>& get_STObjMap();
  vector<string>& get_Array();

  void setCommandMap(unordered_map<string, Command*> &map);
  void setSTSimulatorMap(map<string, Obj*> &map);
  vector<string> lexer(ifstream &in);
  void parser();
};

#endif //ADVANCED__INTERPRETERFLIGHT_H_
