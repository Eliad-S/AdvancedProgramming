//
// Created by eliadsellem on 12/11/19.
//
#include "Obj.h"
mutex m1;
void Obj::setDirection(int d) {
  this->direction = d;
}
void Obj::setValue(float val) {
    m1.lock();
  this->value = val;
  m1.unlock();
}


Obj &Obj::operator++() {
    m1.lock();
  ++this->value;
    m1.unlock();
  return *this;
}
Obj &Obj::operator--() {
    m1.lock();
  --this->value;
  m1.unlock();
  return *this;
}

Obj &Obj::operator++(int) {
    m1.lock();
  this->value++;
  m1.unlock();
  return *this;
}

Obj &Obj::operator--(int) {
    m1.lock();
  --this->value;
  m1.unlock();
  return *this;
}


Obj &Obj::operator+=(float value) {
    m1.lock();
  this->value += value;
  m1.unlock();
  return *this;
}
Obj &Obj::operator-=(float value) {
    m1.lock();
  this->value -= value;
  m1.unlock();
  return *this;
}

float Obj::calculate() {
  return this->value;
}
void Obj::setName(string name) {
  this->valName = name;
}
