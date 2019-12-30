//
// Created by eliadsellem on 12/11/19.
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
    unordered_map<string, pair<string ,Parser *>> functionMap;
    unordered_map<string, Command *> commandMap;
    unordered_map<string, Obj *> STSimulatorMap;
    unordered_map<string, Obj *> STObjMap;


    vector<string> array;
    queue<Obj *> objToUpdate;
    static InterpreterFlight *instance;
    bool keepOpenServerThread;
    bool keepOpenClientThread;
    string sims[36];
    InterpreterFlight() {
        setCommandMap(this->commandMap);
        setSTSimulatorMap(this->STSimulatorMap);
        this->keepOpenServerThread = true;
        this->keepOpenClientThread = true;
        setSimArray();

    }

public:
    OpenControlCommand *controlCommand;
    mutex mutex_;
    mutex mutex_2;
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

    unordered_map<string, Command *>& getCommandMap();


    void setSTSimulatorMap(unordered_map<string, Obj *> &map);

    void setTokens(vector<string> &tokens);

    void done();

    bool getKeepOpenServerThread();

    bool getKeepOpenClientThread();


    unordered_map<string, pair<string ,Parser *>>& getFunctionMap();


    void setSTObjMap(string basic_string, Obj *p_obj);

    void setSimArray();

    string getIndexOfArray(int index);

    Obj *get_STSimulatorObjBySim(string sim);

    void pushQueue(Obj *obj);

    queue<Obj *> &getQueue();

    void popQueue();
    ~InterpreterFlight();
};

#endif //ADVANCED__INTERPRETERFLIGHT_H_