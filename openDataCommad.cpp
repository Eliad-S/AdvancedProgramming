//
// Created by shirgold on 25/12/2019.
//

#include "openDataCommad.h"
#include "InterpreterFlight.h"

void OpenDataCommand::setSimulatorDetails(char buffer[]) {
  string details = buffer;
  string substr = "";
  vector<float> args = splitArgs(details);
  int counter = 0;
  for (float f: args) {
    string sim = InterpreterFlight::getInstance()->getSimByIndex(counter);
    Obj *obj = InterpreterFlight::getInstance()->get_STSimulatorObjBySim(sim);
    if (obj->getDirection() == -1 && !obj->getValueChanged()) {
      obj->setValue(f);
    }
    counter++;
  }
}

int OpenDataCommand::execute(int index) {
  string portS = getArray()[index + 1];
  //check if the its a number
  int port = calculateExpression(InterpreterFlight::getInstance()->get_STObjMap(), portS);
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

void OpenDataCommand::dataServerThread(int server_socket) {
  // while clientThread == true.
  while (InterpreterFlight::getInstance()->getKeepOpenServerThread()) {
    char buffer[1500] = {0};
    read(server_socket, buffer, 1500);
    setSimulatorDetails(buffer);
  }
}

vector<float> OpenDataCommand::splitArgs(string details) {
  int pos = 0;
  vector<float> args;
  int index = details.find("\n");
  int index2 = details.find("\n", index + 1);

  if (index2 < details.length()) {
    details = details.substr(index + 1, details.length() - index - 1);
  }
  string substr = "";
  for (int j = 0; j < 36; j++) {
    if (details.find(",") < details.find("\n")) {
      substr = details.substr(pos, details.find(","));
      float val = stof(substr);
      args.push_back(val);
      details = details.substr(details.find(",") + 1);
    } else {
      substr = details.substr(pos, details.find("\n"));
      float val = stof(substr);
      args.push_back(val);
      break;
    }
  }

  return args;
}