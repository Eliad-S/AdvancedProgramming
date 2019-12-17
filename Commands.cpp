//
// Created by eliadsellem on 12/11/19.
//



#include "InterpreterFlight.h"
#include "ex1.h"

unordered_map<string, Command *> &getCommandMap() {
    return InterpreterFlight::getInstance()->get_CommandMap();
}

map<string, Obj *> &getSTSimulatorMap() {
    return InterpreterFlight::getInstance()->get_STSimulatorMap();
}

unordered_map<string, Obj *> &getSTObjMap() {
    return InterpreterFlight::getInstance()->get_STObjMap();
}

vector<string> &getArray() {
    return InterpreterFlight::getInstance()->get_Array();
}

bool ServerThread() {
    return InterpreterFlight::getInstance()->getServer_Thread();
}

float Command::calculateExpression(unordered_map<string, Obj *> &STObjMap, const string &e) {
    Interpreter *interpreter = new Interpreter(STObjMap);
    Expression *expression = nullptr;
    float result = 0;
// expression
    try {
        expression = interpreter->interpret(e);
        result = expression->calculate();
        delete expression;
        delete interpreter;
    } catch (const char *e) {
        if (expression != nullptr) {
            delete expression;
            delete interpreter;
        }
    }
    return result;
}

void openDataCommand::setSimulatorDetails(char buffer[], int valRead) {
    string details = buffer;
    map<string, Obj *>::iterator it = getSTSimulatorMap().begin();
    string substr = "";
    for (int i = 0; i < valRead; i++) {
        if (details[i] == ',' || details[i] == '\n') {
            float val = stof(substr);
            it->second->setValue(val);
            it++;
            substr = "";
        } else {
            substr += details[i];
        }
    }
}

int openDataCommand::execute(int index) {
    string portS = getArray()[index + 1];
    //check if the its a number****
    int port = stoi(portS);
    char buffer[10000] = {0};
    int socketServer = socket(AF_INET, SOCK_STREAM, 0);
    if (socketServer == -1) {
        //error
        cerr << "could'nt open the socket" << endl;
    }
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(socketServer, (struct sockaddr *) &address, sizeof(address)) == -1) {
        cerr << "could'nt bind the socket to an ip" << endl;
    }
//making socket listen to the port
    if (listen(socketServer, 5) == -1) {
        cerr << "error during listening command" << endl;
    }
//accepting a client.
    int client_socket = accept(socketServer, (struct sockaddr *) &address, (socklen_t *) &address);

    if (client_socket == -1) {
        cerr << "Error accepting clinet" << endl;
    }

    close(socketServer);
    int valRead = read(client_socket, buffer, 10000);
//check
    cout << buffer << endl;

    setSimulatorDetails(buffer, valRead);

    //and after we got the first message from the simulator we can continue compile the rest,
    // and simultaneously continuing receive massage from the simulator.
    thread threadServer([client_socket]() {
        // while clientThread == true.
        while (ServerThread()) {
            sleep(10.0);
            char buffer[10000] = {0};
            int valRead = read(client_socket, buffer, 10000);
            //check
            cout << buffer << endl;

            setSimulatorDetails(buffer, valRead);
        }
    });

    return 2;
}

int varCommand::execute(int index) {
  string varName = getArray()[index +1];
  string simOrEqual = getArray()[index +2];

  if(simOrEqual == "sim") {
    string direction = getArray()[index +3];
    string sim = getArray()[index + 4];
    if(direction == "->")
//    for()
//    Obj* obj;
//    if(direction == "->") {
//      obj = new Obj(varName,)
//    }

  }else{
    if(simOrEqual == "=") {


    }
  }

}

int openControlCommand::execute(int index) {
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        // error
        std::cerr << "could not create a socket" << endl;
        return -1;
    }
    string i = getArray()[index + 1];
    char *ip;
    strcpy(ip, i.c_str());
    int port = stoi(getArray()[index + 2]);
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(port);
    int isConnect = connect(clientSocket, (struct sockaddr *) &address, sizeof(address));
    if (isConnect == -1) {
        //
        return -2;
    } else {
        //
    }
    thread threadClient([clientSocket]() {
        auto t = getSTObjMap().begin();
        for (auto it = getSTObjMap().begin(); it != getSTObjMap().end(); ++it) {
            Obj *obj = it->second;
            string sim = obj->getSim();
            float val = obj->getValue();
            string massage = "set " + sim + " " + to_string(val) + "\r\n";
            char *m;
            strcpy(m, massage.c_str());
            int is_send = send(clientSocket, m, strlen(m), 0);
            if (is_send == -1) {

            } else {

            }
        }
    });
    return 3;
}

int ifCommand::execute(int index) {
    bool flag = false;
    int counter = 1;
    string s1 = getArray()[index + 1];
    string s2 = getArray()[index + 2];
    if (s2 == "{") {
        counter = 3;
        flag = checkCondition1(s1, getSTObjMap());
//        //find if s1 is true value.
//        auto it  = STObjMap.find(s1);
//        // variable
//        if (STObjMap.find(s1) != STObjMap.end()) {
//            float val = it->second->getValue();
//            if (val > 0) {
//                flag = true;
//            }
//        } else {
//            // number
//            regex isFloat("[-]?([0-9]*[.])?[0-9]+");
//            if (regex_match(s1, isFloat)) {
//                if (stof(s1)) {
//                    flag = true;
//                }
//            } else {
//                if(calculateExpression(STObjMap,s1) > 0) {
//                  flag = true;
//                }
//            }
//        }
    } else {
        counter = 5;
        string s3 = getArray()[index + 3];
        flag = checkCondition2(s1, s2, s3, getSTObjMap());
    }
    if (!flag) {
        while (getArray()[index + counter] != "}") {
            counter++;
        }
        return counter;
    } else {
        while (getArray()[index + counter] != "}") {
            Command *c = getCommandMap().find(getArray()[index + counter])->second;
            counter += c->execute(index);
        }
    }
    return counter;
}

int whileCommand::execute(int index) {
    bool flag = false;
    int counter = 1;
    string s1 = getArray()[index + 1];
    string s2 = getArray()[index + 2];
    if (s2 == "{") {
        counter = 3;
        // find if s1 is true value.
        auto it = getSTObjMap().find(s1);
        // variable
        if (getSTObjMap().find(s1) != getSTObjMap().end()) {
            float val = it->second->getValue();
            if (val > 0) {
                flag = true;
            }
        } else {
            // number
            regex isFloat("[-]?([0-9]*[.])?[0-9]+");
            if (regex_match(s1, isFloat)) {
                if (stof(s1)) {
                    flag = true;
                }
            } else {
                if (calculateExpression(getSTObjMap(), s1) > 0) {
                    flag = true;
                }
            }
        }
    } else {
        counter = 5;
        string s3 = getArray()[index + 3];
        // expression
        float f1 = calculateExpression(getSTObjMap(), s1);
        float f3 = calculateExpression(getSTObjMap(), s3);
    }
}

bool conditionParser::checkCondition1(string var,
                                      unordered_map<string, Obj *> &STObjMap) {
    float val = calculateExpression(STObjMap, var);
    if (val) {
        return true;
    }
    return false;
}

bool conditionParser::checkCondition2(string var1, string condition, string var2,
                                      unordered_map<string, Obj *> &STObjMap) {
    bool flag = false;
    float val1 = calculateExpression(STObjMap, var1);
    float val2 = calculateExpression(STObjMap, var2);
    if (condition == "!=") {
        flag = (val1 != val2);
    }
    if (condition == "==") {
        flag = (val1 == val2);
    }
    if (condition == ">=") {
        flag = (val1 >= val2);
    }
    if (condition == "<=") {
        flag = (val1 <= val2);
    }
    if (condition == ">") {
        flag = (val1 > val2);
    }
    if (condition == "<") {
        flag = (val1 < val2);
    }
    return flag;
}

int printCommand::execute(int index) {
    cout << getArray()[index + 1] << endl;
}

int sleepCommand::execute(int index) {
    sleep(stoi(getArray()[index + 1]));
}

int objCommand::execute(int index) {
    return 0;
}