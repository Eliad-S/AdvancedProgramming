//
// Created by eliadsellem on 12/11/19.
//

#ifndef ADVANCED__OBJ_H_
#define ADVANCED__OBJ_H_
#include <string>
#include "Expression.h"
#include <mutex>
using namespace std;


class Obj : public Expression{
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
  Obj(string name ,float val){
    this->valName = name;
    this->value = val;
    valueChanged = false;
  }
  Obj(string name ,string& s, int d){
    this->valName = name;
    this->value = 0;
    this->sim = s;
    this->direction = d;
    valueChanged = false;
  }
  void setDirection(int d);
  void setValue(float val);
  //prefix
  Obj &operator++();
  Obj &operator--();

  //postfix.
  Obj &operator++(int);
  Obj &operator--(int);

  Obj &operator-=(float val);
  Obj &operator+=(float val);

  float calculate() override;
  float getValue() {
    return this->value;
  }

  string getSim(){
    return this->sim;
  }

  void setName(string basic_string);

  int getDirection();
  void setSim(string basic_string);
  void setValueChanged(bool condition);
  ~Obj(){};
  bool getValueChanged();
  string createSetSim();
};


#endif //ADVANCED__OBJ_H_
