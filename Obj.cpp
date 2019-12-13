//
// Created by eliadsellem on 12/11/19.
//
#include "Obj.h"

void Obj::setDirection(int d) {
  this->direction = d;
}
void Obj::setValue(int val) {
  this->value = val;
<<<<<<< HEAD
=======
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
>>>>>>> origin/master
}