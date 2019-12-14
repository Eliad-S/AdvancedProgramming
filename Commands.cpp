//
// Created by eliadsellem on 12/11/19.
//
#include <regex>
#include "Commands.h"
#include "Obj.h"
#include "Obj.cpp"
int openDataCommand::execute(vector<string> &array,
                             int index,
                             unordered_map<string, Obj *> &STSimulatorMap,
                             unordered_map<string, Obj *> &STObjMap,
                             unordered_map<string, Command*> &commandMap) {
  string portS = array[index + 1];
  //check if the its a number****
  int port = stoi(portS);
  char buffer[1024] = {0};
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
  if (listen(socketServer, 1) == -1) {
    cerr << "error during listening command" << endl;
  }
//accepting a client.
  int client_socket = accept(socketServer, (struct sockaddr *) &address, (socklen_t *) &address);

  if (client_socket == -1) {
    cerr << "Error accepting clinet" << endl;
  }

  close(socketServer);
  int valRead = read(client_socket, buffer, 1024);
//check
  cout << buffer << endl;

  //setDetails(buffer, valRead ,STSimulatorMap);

  //and after we got the first message from the simulator we can continue compile the rest,
  // and simultaneously continuing receive massage from the simulator.
  thread threadServer([client_socket]() {
    while (true) {
      char buffer[1024] = {0};
      int valRead = read(client_socket, buffer, 1024);
      //check
      cout << buffer << endl;

      //setDetails(buffer,velRead ,STSimulatorMap);});
    }
  });
  return 2;
}

int varCommand::execute(vector<string> &array,
                        int index,
                        unordered_map<string, Obj *> &STSimulatorMap,
                        unordered_map<string, Obj *> &STObjMap,
                        unordered_map<string, Command*> &commandMap) {

}

int openControlCommand:: execute(vector<string> &array,
                                 int index,
                                 unordered_map<string, Obj *> &STSimulatorMap,
                                 unordered_map<string, Obj *> &STObjMap,
                                 unordered_map<string, Command*> &commandMap) {
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        // error
        std::cerr<<"could not create a socket"<<endl;
        return -1;
    }
    string i = array[index + 1];
    char* ip;
    strcpy(ip, i.c_str());
    int port = stoi(array[index + 2]);
    sockaddr_in adress;
    adress.sin_family = AF_INET;
    adress.sin_addr.s_addr = inet_addr("127.0.0.1");
    adress.sin_port = htons(port);
    int isConnect = connect(clientSocket,(struct sockaddr *)&adress, sizeof(adress));
    if (isConnect == -1) {
        //
        return -2;
    } else {
        //
    }
    thread threadClient([clientSocket, STObjMap]() {
        auto t = STObjMap.begin();
        for ( auto it = STObjMap.begin(); it != STObjMap.end(); ++it ) {
            Obj* obj = it->second;
            string sim = obj->getSim();
            float val = obj->getValue();
            string massage = "set " + sim + " " + to_string(val) + "\r\n";
            char* m;
            strcpy(m, massage.c_str());
            int is_send = send(clientSocket, m, strlen(m), 0);
            if (is_send == -1) {


            } else {

            }
        }
    });
    return 3;
}


int ifCommand:: execute(vector<string> &array,
                        int index,
                        unordered_map<string, Obj *> &STSimulatorMap,
                        unordered_map<string, Obj *> &STObjMap,
                        unordered_map<string, Command*> &commandMap) {
    bool flag = false;
    int counter = 1;
    string s1 = array[index + 1];
    string s2 = array[index + 2];
    if (s2 == "{") {
        counter = 3;
        //find if s1 is true value.
        auto it  = STObjMap.find(s1);
        // variable
        if (STObjMap.find(s1) != STObjMap.end()) {
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
                // expression
            }
        }
    } else {
        counter = 5;
        string s3 = array[index + 3];
        // expression
        float f1 = stof(s1);
        float f3 = stof(s3);
        if (s2 == "!=") {
            flag = (f1 != f3);
        }
        if (s2 == "==") {
            flag = (f1 == f3);
        }
        if (s2 == ">=") {
            flag = (f1 >= f3);
        }
        if (s2 == "<=") {
            flag = (f1 <= f3);
        }
        if (s2 == ">") {
            flag = (f1 > f3);
        }
        if (s2 == "<") {
            flag = (f1 < f3);
        }
    }
    if (!flag) {
        while (array[index + counter] != "}") {
            counter++;
        }
        return counter;
    } else {
        while (array[index + counter] != "}") {
            Command* c = commandMap.find(array[index + counter])->second;
            counter += c->execute(array, index, STSimulatorMap,
                    STObjMap, commandMap);
        }
    }
    return counter;
}