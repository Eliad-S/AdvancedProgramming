//
// Created by eliadsellem on 11/4/19.
//

#ifndef EX1__EXPRESSION_H_
#define EX1__EXPRESSION_H_
using namespace std;
/**
 * Expression Interface
 */
class Expression {

 public:
  virtual float calculate() = 0;
  virtual ~Expression() {}
};

#endif //EX1__EXPRESSION_H_
