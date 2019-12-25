//
// Created by shirgold on 25/12/2019.
//

#ifndef ADVANCEDPROGRAMMING_OPENDATACOMMAD_H
#define ADVANCEDPROGRAMMING_OPENDATACOMMAD_H


#include "Command.h"

class OpenDataCommand : public Command {
    virtual int execute(int index);
public:
    static void dataServerThread(int client_socket);
    static void setSimulatorDetails(char buffer[], int valRead);
    static vector<float> splitArgs(string basic_string);
};


#endif //ADVANCEDPROGRAMMING_OPENDATACOMMAD_H
