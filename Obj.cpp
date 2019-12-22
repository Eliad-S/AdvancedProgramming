//
// Created by eliadsellem on 12/11/19.
//
#include "Obj.h"
#include "InterpreterFlight.h"
mutex m1;
void Obj::setDirection(int d) {
  this->direction = d;
}
void Obj::setValue(float val) {
  InterpreterFlight::getInstance()->mutex_.lock();
  this->value = val;
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
  InterpreterFlight::getInstance()->mutex_.lock();
  this->valName = name;
  InterpreterFlight::getInstance()->mutex_.unlock();
}

int Obj::getDirection() {
  return this->direction;

}
