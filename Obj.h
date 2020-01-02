//
// Created by shirgold and EliadSellem on 26/12/2019.
//

#ifndef ADVANCED__OBJ_H_
#define ADVANCED__OBJ_H_

#include <string>
#include "Expression.h"
#include <mutex>

using namespace std;

class Obj : public Expression {
    string valName = " ";
    float value = 0;
    string sim;
    int direction = 0;
    bool valueChanged;

public:
    Obj(const string s) {
        this->sim = s;
        valueChanged = false;
    }

    Obj(string name, float val) {
        this->valName = name;
        this->value = val;
        valueChanged = false;
    }

    Obj(string name, string &s, int d) {
        this->valName = name;
        this->value = 0;
        this->sim = s;
        this->direction = d;
        valueChanged = false;
    }
    /*
     * the function sets the direction of the variable (-> is 1, <- is -1).
     */
    void setDirection(int d);
    /*
     * the function sets the value of the variable.
     */
    void setValue(float val);

    //prefix
    Obj &operator++();

    Obj &operator--();

    //postfix.
    Obj &operator++(int);

    Obj &operator--(int);

    Obj &operator-=(float val);

    Obj &operator+=(float val);
    /*
     * the function returns the value of the variable.
     */
    float calculate() override;
    /*
     * the function returns the value of the variable.
     */
    float getValue();
    /*
     * the function returns the sim of the variable.
     */
    string getSim();
    /*
     * the function sets the name of the variable.
     */
    void setName(string basic_string);
    /*
     * returns the direction of the variable (-> is 1, <- is -1).
     */
    int getDirection();
    /*
     * The function get a new condition to set our condition
     * this condition will be change to be True if the interpreter change an existing
     * value, that's mean not update this specific value from the Simulator until we notify
     * him of the new value
     */
    void setValueChanged(bool condition);
    /*
     * the function returns the valueChanged.
     */
    bool getValueChanged();
    /*
     * the function creates the messege for the simulator
     */
    string createSetSim();
    /*
     * the function returns the name of the variable.
     */
    string getName();
    // destructor
    ~Obj() {};

};


#endif //ADVANCED__OBJ_H_
