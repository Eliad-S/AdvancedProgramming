//
// Created by eliadsellem on 12/11/19.
//
#include "Obj.h"
mutex m;
void Obj::setDirection(int d) {
  this->direction = d;
}
void Obj::setValue(float val) {
    m.lock();
  this->value = val;
  m.unlock();
}


Obj &Obj::operator++() {
    m.lock();
  ++this->value;
    m.unlock();
  return *this;
}
Obj &Obj::operator--() {
    m.lock();
  --this->value;
  m.unlock();
  return *this;
}

Obj &Obj::operator++(int) {
    m.lock();
  this->value++;
  m.unlock();
  return *this;
}

Obj &Obj::operator--(int) {
    m.lock();
  --this->value;
  m.unlock();
  return *this;
}

Obj &Obj::operator+=(float value) {
    m.lock();
  this->value += value;
  m.unlock();
  return *this;
}
Obj &Obj::operator-=(float value) {
    m.lock();
  this->value -= value;
  m.unlock();
  return *this;
}

float Obj::calculate() {
  return this->value;
}
void Obj::setName(string name) {
  this->valName = name;
}
