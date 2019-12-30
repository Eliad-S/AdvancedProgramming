//
// Created by shirgold on 30/12/2019.
//

#include "Parser.h"
#include "InterpreterFlight.h"


void Parser:: interpret() {
    unsigned int index = this->start;
    while (index < limit) {
        unordered_map<string, Command *>::iterator itCommand;
        itCommand = InterpreterFlight::getInstance()->get_CommandMap().find(array[index]);
        if (itCommand != InterpreterFlight::getInstance()->get_CommandMap().end()) {
            Command *c = InterpreterFlight::getInstance()->get_CommandMap().find(array[index])->second;
            index += c->execute(index);
        }
    }
    cout<< "end parser"<<endl;

}
