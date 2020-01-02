//
// Created by shirgold and EliadSellem on 26/12/2019.
//

#include "Parser.h"
#include "InterpreterFlight.h"


void Parser:: interpret() {
    int index = this->start;
    while (index < limit) {
        unordered_map<string, Command *>::iterator itCommand;
        itCommand = InterpreterFlight::getInstance()->get_CommandMap().find(array[index]);
        if (itCommand != InterpreterFlight::getInstance()->get_CommandMap().end()) {
            Command *c = InterpreterFlight::getInstance()->get_CommandMap().find(array[index])->second;
            index += c->execute(index);
        }
    }
}
