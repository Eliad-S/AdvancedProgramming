//
// Created by eliadsellem on 12/11/19.
//
#include "Obj.h"
#include "InterpreterFlight.h"

void Obj::setDirection(int d) {
  this->direction = d;
}
void Obj::setValue(float val) {
    m1.lock();
    this->value = val;
    m1.unlock();
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


Obj &Obj::operator+=(float value) {
  this->value += value;
  return *this;
}
Obj &Obj::operator-=(float value) {
  this->value -= value;
  return *this;
}

float Obj::calculate() {
  return this->value;
}
void Obj::setName(string name) {
  this->valName = name;
}

int Obj::getDirection() {
    return this->direction;
}
