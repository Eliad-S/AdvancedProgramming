//
// Created by eliadsellem on 12/11/19.
//

#ifndef ADVANCED__INTERPRETERFLIGHT_H_
#define ADVANCED__INTERPRETERFLIGHT_H_
#include <vector>
#include <fstream>
#include "Commands.cpp"
#include "Obj.cpp"
#include <unordered_map>


using namespace std;

class InterpreterFlight {
  unordered_map<string, Command*> commandMap;
  map<string, Obj*> STSimulatorMap;
  unordered_map<string, Obj*> STObjMap;
  vector<string> array;

 public:
  void setCommandMap(unordered_map<string, Command*> &map);
  void setSTSimulatorMap(map<string, Obj*> &map);
  vector<string> lexer(ifstream &in);

  InterpreterFlight(ifstream &inFile) {
    this->commandMap =unordered_map<string, Command*>();
    this->STSimulatorMap = map<string, Obj*>();
    this->STObjMap = unordered_map<string, Obj*>();
    this->array = lexer(inFile);
    setCommandMap(this->commandMap);
    setSTSimulatorMap(this->STSimulatorMap);
    inFile.close();
  }

  void parser();
};
#endif //ADVANCED__INTERPRETERFLIGHT_H_
