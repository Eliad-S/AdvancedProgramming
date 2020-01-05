//
// Created by shirgold and EliadSellem on 26/12/2019.
//

#include "OpenControlCommand.h"
#include "InterpreterFlight.h"

int OpenControlCommand::execute(int index) {

  InterpreterFlight::getInstance()->controlCommand = this;
  int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (clientSocket == -1) {
    // error
    std::cerr << "could not create a socket" << endl;
    return -1;
  }
  string i = getArray()[index + 1];
  const char *ip = i.c_str();
  int port = calculateExpression(InterpreterFlight::getInstance()->get_STObjMap(), getArray()[index + 2]);
  sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = inet_addr(ip);
  address.sin_port = htons(port);
  int isConnect = connect(clientSocket, (struct sockaddr *) &address, sizeof(address));
  if (isConnect == -1) {
    cerr << "could not connect to the simulator" << endl;
    return -2;
  }
  //open a new thread that will open connection with the simulator as a client
  InterpreterFlight::getInstance()->clientThread = thread([clientSocket, this]() {

    while (InterpreterFlight::getInstance()->getKeepOpenClientThread()) {
      //update the simulator of values that have been changed in our program while compiling,
      //that have been put in the queue of value to update.
      while (!InterpreterFlight::getInstance()->getQueue().empty()) {
        InterpreterFlight::getInstance()->mutex_2.lock();
        string message = InterpreterFlight::getInstance()->getQueue().front()->createSetSim();
        InterpreterFlight::getInstance()->getQueue().front()->setValueChanged(false);
        const char *p = message.c_str();
        int is_send = send(clientSocket, p, strlen(p), 0);
        if (is_send == -1) {
        }
        InterpreterFlight::getInstance()->getQueue().pop();
        InterpreterFlight::getInstance()->mutex_2.unlock();

      }
      //wait until someone will inform us that we need to update new values.
      unique_lock<mutex> ul(m);
      cv.wait(ul);
    }
    close(clientSocket);
  });
  return 3;
}