//
// Created by shirgold and EliadSellem on 26/12/2019.
//
#include "Obj.h"
#include "InterpreterFlight.h"
mutex m1;
void Obj::setDirection(int d) {
  InterpreterFlight::getInstance()->mutex_.lock();
  this->direction = d;
  InterpreterFlight::getInstance()->mutex_.unlock();
}
void Obj::setValue(float val) {
  InterpreterFlight::getInstance()->mutex_.lock();
  if(!valueChanged) {
    this->value = val;
  }
  InterpreterFlight::getInstance()->mutex_.unlock();
}


Obj &Obj::operator++() {
  ++this->value;
  return *this;
}
Obj &Obj::operator--() {
  --this->value;
  return *this;
}

Obj &Obj::operator++(int) {
  this->value++;
  return *this;
}

Obj &Obj::operator--(int) {
  --this->value;
  return *this;
}


Obj &Obj::operator+=(float value1) {
  this->value += value1;
  return *this;
}
Obj &Obj::operator-=(float value1) {
  this->value -= value1;
  return *this;
}

float Obj:: getValue() {
    return this->value;
}

string Obj:: getSim() {
    return this->sim;
}

float Obj::calculate() {
  return this->value;
}
void Obj::setName(string name) {
  InterpreterFlight::getInstance()->mutex_.lock();
  this->valName = name;
  InterpreterFlight::getInstance()->mutex_.unlock();
}

int Obj::getDirection() {
  return this->direction;

}

bool Obj::getValueChanged() {
  return this->valueChanged;
}

void Obj::setValueChanged(bool condition) {
  InterpreterFlight::getInstance()->mutex_.lock();
  this->valueChanged = condition;
  InterpreterFlight::getInstance()->mutex_.unlock();
}

string Obj :: createSetSim(){
  string simUpdate = "set " + sim + " " + to_string(value) + "\r\n";
  return simUpdate;
}
string Obj:: getName() {
    return this->valName;
}
