//
// Created by shirgold and EliadSellem on 25/12/2019.
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
