//
// Created by shirgold and EliadSellem on 26/12/2019.
//

#ifndef ADVANCED__INTERPRETERFLIGHT_H_
#define ADVANCED__INTERPRETERFLIGHT_H_

#include <vector>
#include <fstream>
#include <unordered_map>
#include "openDataCommad.h"
#include "OpenControlCommand.h"
#include "VarCommand.h"
#include "PrintCommand.h"
#include "SleepCommand.h"
#include "ObjCommand.h"
#include "WhileCommand.h"
#include "IfCommand.h"
#include "Parser.h"

using namespace std;

class InterpreterFlight {
  //key - the name of the function. value - Parser contain the interval of the function in "array"
  unordered_map<string, pair<string, Parser *>> functionMap;
  //key - the name of the Command. value - an instance of the relevant command
  unordered_map<string, Command *> commandMap;
  //key - the name of variable by the xml file. value - relevant Obj type.
  unordered_map<string, Obj *> STSimulatorMap;
  //key - the name of variable by interpreter file "file.txt". value - relevant Obj type.
  unordered_map<string, Obj *> STObjMap;

  //the interpreter file splited to tokens
  vector<string> array;
  //structure that contains obj that need to be update by our client to the simulator.
  queue<Obj *> objToUpdate;
  static InterpreterFlight *instance;
  //bool type for the server "while" thread
  bool keepOpenServerThread;
  //bool type for the client "while" thread
  bool keepOpenClientThread;
  string sims[36];
  //constructor
  InterpreterFlight() {
    setCommandMap(this->commandMap);
    setSTSimulatorMap(this->STSimulatorMap);
    this->keepOpenServerThread = true;
    this->keepOpenClientThread = true;
    setSimArray();

  }

 public:
  //save an instance of "controlCommand" for having access to "cv" and "m" files.
  OpenControlCommand *controlCommand;
  mutex mutex_;
  mutex mutex_2;
  //threads
  thread clientThread;
  thread serverThread;

  //singleton
  static InterpreterFlight *getInstance() {
    if (!instance)
      instance = new InterpreterFlight();
    return instance;
  }

  unordered_map<string, Command *> &get_CommandMap();

  unordered_map<string, Obj *> &get_STSimulatorMap();

  unordered_map<string, Obj *> &get_STObjMap();

  vector<string> &get_Array();
  /*
   * set our CommandMap with keys to relevant Commands
   */
  void setCommandMap(unordered_map<string, Command *> &map);
  /*
   * set our STSimulatorMap by Keys of the names of variables in the xml file
   * and Value as an Obj instance that contains the Sim of it in the xml.
   */
  void setSTSimulatorMap(unordered_map<string, Obj *> &map);

  void setTokens(vector<string> &tokens);
  /*
   * finish the thread process
   */
  void done();

  bool getKeepOpenServerThread();

  bool getKeepOpenClientThread();

  unordered_map<string, pair<string, Parser *>> &getFunctionMap();

  void setSTObjMap(string basic_string, Obj *p_obj);
  /*
   * set the "simArray" by the order in the xml file.
   */
  void setSimArray();
  /*
   * get the sim in "simArray" in the "index" place
   */
  string getSimByIndex(int index);
  /*
   * return the Obj in our STObjMap that contain the "sim" given
   */
  Obj *get_STSimulatorObjBySim(string sim);
  /*
   * push an obj to our objToUpdate Queue.
   */
  void pushQueue(Obj *obj);
  /*
   * return objToUpdate
   */
  queue<Obj *> &getQueue();
  /*
   * destructor
   */
  ~InterpreterFlight();
};

#endif //ADVANCED__INTERPRETERFLIGHT_H_