//
// Created by shirgold on 25/12/2019.
//

#ifndef ADVANCEDPROGRAMMING_OPENCONTROLCOMMAND_H
#define ADVANCEDPROGRAMMING_OPENCONTROLCOMMAND_H


#include "Command.h"

class OpenControlCommand : public Command {
    queue<Obj *> objToUpdate;
    virtual int execute(int index);

    queue<Obj *> &getQueue();

    void pushQueue(Obj *obj);

public:
    condition_variable cv;
    mutex m;
};

#endif //ADVANCEDPROGRAMMING_OPENCONTROLCOMMAND_H
