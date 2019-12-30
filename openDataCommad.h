//
// Created by shirgold on 25/12/2019.
//

#ifndef ADVANCEDPROGRAMMING_OPENDATACOMMAD_H
#define ADVANCEDPROGRAMMING_OPENDATACOMMAD_H


#include "Command.h"

class OpenDataCommand : public Command {
    /*
     * open a connection with the Simulator server.
     * after the connection has been succeeded the function open a new thread
     * and keep in touch with the Simulator that update us all the value that are
     * declared in the xml file, and update them in our data.
     */
    virtual int execute(int index);
public:
    /*
     * function the perform a while loop and receive data from the server
     * until the condition will be false
     */
    static void dataServerThread(int client_socket);
    /*
     * the function sets the values from the simulator in the map.
     */
    static void setSimulatorDetails(char buffer[]);
    /*
     * the function splits the values from the simulator by ','.
     */
    static vector<float> splitArgs(string basic_string);
};


#endif //ADVANCEDPROGRAMMING_OPENDATACOMMAD_H
