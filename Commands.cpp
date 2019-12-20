//
// Created by eliadsellem on 12/11/19.
//
#include "InterpreterFlight.h"
#include "ex1.h"

condition_variable cv;
mutex m;

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

bool keepRunningServerThread() {
    return InterpreterFlight::getInstance()->getKeepOpenServerThread();
}

bool keepRunningClientThread() {
    return InterpreterFlight::getInstance()->getKeepOpenClientThread();
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
    int i = 0;
    string substr = "";
    int index = details.find("\n");
    int index2 = details.find("\n", index + 1);
    if (index2 < details.length()) {
        i = index + 1;
    }
    map<string, Obj *>::iterator it = getSTSimulatorMap().begin();
    for (; it != getSTSimulatorMap().end(); it++) {
        if (details.find(",", i) < details.find("\n", i)) {
            substr = details.substr(i, details.find(",", i) - i);
            float val = stof(substr);
            it->second->setValue(val);
            i = details.find(",", i) + 1;
        } else {
            substr = details.substr(i, details.find("\n", i) - i);
            float val = stof(substr);
            it->second->setValue(val);
            break;
        }
    }
}

int openDataCommand::execute(int index) {
    string portS = getArray()[index + 1];
    //check if the its a number
    int port = stoi(portS);
    char buffer[791] = {0};
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        //error
        cerr << "could'nt open the socket" << endl;
    }
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(sockfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        cerr << "could'nt bind the socket to an ip" << endl;
    }
//making socket listen to the port
    if (listen(sockfd, 5) == -1) {
        cerr << "error during listening command" << endl;
    }
//accepting a client.
    int server_socket = accept(sockfd, (struct sockaddr *) &address, (socklen_t *) &address);

    if (server_socket == -1) {
        cerr << "Error accepting clinet" << endl;
    }

    close(sockfd);
    //and after we got the first message from the simulator we can continue compile the rest,
    // and simultaneously continuing receive massage from the simulator.
    InterpreterFlight::getInstance()->serverThread = thread(dataServerThread, server_socket);
    return 2;
}

void openDataCommand::dataServerThread(int server_socket) {
    // while clientThread == true.
    while (keepRunningServerThread()) {
        InterpreterFlight::getInstance()->mutex_.lock();
        sleep(3.0);
        char buffer[791] = {0};
        int valRead = read(server_socket, buffer, 791);
        //check
        //cout << buffer << endl;
        setSimulatorDetails(buffer, valRead);
        InterpreterFlight::getInstance()->mutex_.unlock();
    }
}

int varCommand::execute(int index) {
    string varName = getArray()[index + 1];
    string flashOrEqual = getArray()[index + 2];
    string simOrExpression = getArray()[index + 3];
    Obj *obj;

    //var name ->/<- sim
    if (simOrExpression == "sim") {
        string sim = getArray()[index + 4];
        if (flashOrEqual == "->") {
            obj = new Obj(varName, sim, 1);
            getSTObjMap()[varName] = obj;
        } else {
            map<string, Obj *>::iterator it;
            for (it = getSTSimulatorMap().begin(); it != getSTSimulatorMap().end(); it++) {
                obj = it->second;
                if (obj->getSim() == sim) {
                    obj->setName(varName);
                    getSTObjMap()[varName] = obj;
                    break;
                }
            }
        }
        cv.notify_one();
        return 5;
    } else {
        if (flashOrEqual == "=") {
            float value = 0;
            string expression = getArray()[index + 3];
            regex isFloat("[-]?([0-9]*[.])?[0-9]+");
            if (regex_match(expression, isFloat)) {
                value = stof(expression);
            } else {
                value = calculateExpression(getSTObjMap(), expression);
            }
            obj = new Obj(varName, value);
            getSTObjMap()[varName] = obj;
        }
        cv.notify_one();
        return 4;
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
    const char *ip = i.c_str();
    int port = stoi(getArray()[index + 2]);
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ip);
    address.sin_port = htons(port);
    int isConnect = connect(clientSocket, (struct sockaddr *) &address, sizeof(address));
    if (isConnect == -1) {
        cerr << "could not connect to the simulator" << endl;
        return -2;
    }
    InterpreterFlight::getInstance()->clientThread = thread([clientSocket]() {
        while (keepRunningClientThread()) {
            InterpreterFlight::getInstance()->mutex_.lock();
            for (auto it = getSTObjMap().begin(); it != getSTObjMap().end(); ++it) {
                Obj *obj = it->second;
                if (obj->getDirection() == 1) {
                    string sim = obj->getSim();
                    float val = obj->getValue();
                    string massage = "set " + sim + " " + to_string(val) + "\r\n";
                    const char *p = massage.c_str();
                    int is_send = send(clientSocket, p, strlen(p), 0);
                    if (is_send == -1) {
                    }
                    InterpreterFlight::getInstance()->mutex_.unlock();
                }
            }
            unique_lock<mutex> ul(m);
            cv.wait(ul);
        }
        close(clientSocket);
    });
    return 3;
}


int ifCommand::execute(int index) {
    bool flag;
    int counter;
    string v1 = getArray()[index + 1];
    string v2 = getArray()[index + 2];
    if (v2 == "{") {
        counter = 3;
        flag = checkCondition1(v1);
    } else {
        counter = 5;
        string v3 = getArray()[index + 3];
        flag = checkCondition2(v1, v2, v3);
    }
    if (!flag) {
        while (getArray()[index + counter] != "}") {
            counter++;
        }
        return counter;
    } else {
        while (getArray()[index + counter] != "}") {
            Command *c = getCommandMap().find(getArray()[index + counter])->second;
            counter += c->execute(index + counter);
        }
    }
    return counter;
}

int whileCommand::execute(int index) {
    bool flag;
    int counter1;
    int counter2;
    int whichCondition;
    string v1 = getArray()[index + 1];
    string v2 = getArray()[index + 2];
    string v3;
    if (v2 == "{") {
        counter1 = 3;
        flag = checkCondition1(v1);
        whichCondition = 1;
    } else {
        counter1 = 4;
        v3 = getArray()[index + 3];
        flag = checkCondition2(v1, v2, v3);
        whichCondition = 2;
    }
    counter2 = counter1;
    while (getArray()[index + counter2] != "}") {
        counter2++;
    }
    counter2++;
    if (!flag) {
        return counter2;
    }
    if (whichCondition == 1) {
        while (checkCondition1(v1)) {
            counter1 = 3;
            while (getArray()[index + counter1] != "}") {
                Command *c = getCommandMap().find(getArray()[index + counter1])->second;
                counter1 += c->execute(index);
            }
        }
    } else {
        while (checkCondition2(v1, v2, v3)) {
            counter1 = 5;
            while (getArray()[index + counter1] != "}") {
                Command *c = getCommandMap().find(getArray()[index + counter1])->second;
                counter1 += c->execute(index + counter1);
            }
        }
    }
    return counter2;
}

bool conditionParser::checkCondition1(string var) {
    float val = calculateExpression(getSTObjMap(), var);
    if (val) {
        return true;
    }
    return false;
}

bool conditionParser::checkCondition2(string var1, string condition, string var2) {
    bool flag = false;
    float val1 = calculateExpression(getSTObjMap(), var1);
    float val2 = calculateExpression(getSTObjMap(), var2);
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
    auto obj = getSTObjMap().find(getArray()[index + 1]);
    if (obj != getSTObjMap().end()) {
        cout << obj->second->getValue() << endl;
    } else {
        cout << getArray()[index + 1] << endl;
    }
    return 2;
}

int sleepCommand::execute(int index) {
    sleep(stoi(getArray()[index + 1]));
    return 2;
}

//need to check for this options: ++ -- /=, x = y + z, x = y - z, x = y * z,  x = y/z.
int objCommand::execute(int index) {
    string name = getArray()[index + 1];
    string expression = getArray()[index + 3];
    float value = calculateExpression(getSTObjMap(), expression);
    unordered_map<string, Obj *>::iterator it = getSTObjMap().find(name);
    it->second->setValue(value);
    cv.notify_one();
    return 4;
}