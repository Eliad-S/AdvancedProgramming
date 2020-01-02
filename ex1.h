//
// Created by shirgold and EliadSellem on 25/12/2019.
//

#ifndef EX1__EX1_H_
#define EX1__EX1_H_
#include <map>
#include "Expression.h"
#include "math.h"
#include "iostream"
#include <vector>
#include "map"
#include <regex>
#include <stack>
#include <unordered_map>
#include "queue"
#include "Obj.h"

class Value : public Expression {
  const float val;
 public:
  //constructor
  Value(float v) : val(v) {}
  //return the value.
  float calculate() override;
};

class UnaryOperator : public Expression {
 protected:
  Expression *exP{nullptr};
 public:
  //constructor
  UnaryOperator(Expression *exp) {
    this->exP = exp;
  }
  //destructor
  ~UnaryOperator() {
    delete (exP);
  }
};

class UPlus : public UnaryOperator {

 public:
  //constructor
  UPlus(Expression *exp) : UnaryOperator(exp) {};
  //calculate the expression filed in Uplus and return its value.
  float calculate() override;
};

class UMinus : public UnaryOperator {
 public:
  //constructor
  UMinus(Expression *exp) : UnaryOperator(exp) {}
  //calculate the expression filed in UMinus and return its value.
  float calculate();

};

class BinaryOperator : public Expression {
 protected:
  Expression *exP1{nullptr};
  Expression *exP2{nullptr};
  //constructor
  BinaryOperator(Expression *exp1, Expression *exp2) : exP1(exp1), exP2(exp2) {}

 public:
  //destructor
  ~BinaryOperator() {
    delete (exP1);
    delete (exP2);
  }
};

class Plus : public BinaryOperator {
 public:
  //constructor
  Plus(Expression *exp1, Expression *exp2) : BinaryOperator(exp1, exp2) {}
  //calculate both expression filed in Plus and return the calculation of them with the operator +
  float calculate() override;
};

class Minus : public BinaryOperator {
 public:
  //constructor
  Minus(Expression *exp1, Expression *exp2) : BinaryOperator(exp1, exp2) {}
  //calculate both expression filed in Plus and return the calculation of them with the operator -
  float calculate() override;
};

class Mul : public BinaryOperator {
 public:
  //constructor
  Mul(Expression *exp1, Expression *exp2) : BinaryOperator(exp1, exp2) {}
  //calculate both expression filed in Plus and return the calculation of them with the operator *
  float calculate() override;
};

class Div : public BinaryOperator {
 public:
  //constructor
  Div(Expression *exp1, Expression *exp2) : BinaryOperator(exp1, exp2) {}
  //calculate both expression filed in Plus and return the calculation of them with the operator /
  float calculate() override;
};
/*
 * Token its a singleton class that sort an expression by its purpose - numbers,operators,brace and variables
 */
class Token {

  //if its a number.
  float value = 0;
  //if its an operator.
  char symbol = ' ';
  int precedence = 0;
  bool binary = false;
  //if its a variable.
  string parameter;

  Token() {}

 public:
  enum TokenType {
    Nothing,
    Number,
    Operator,
    LeftBrace,
    RightBrace,
    Variable
  };

  TokenType token_type = TokenType(Nothing);
  /*
   * The function receive a vector of string and return a vector of Tokens.
   */
  static vector<Token *> stringsToTokens(vector<string> vToken);
  /*
   * return the value of the token.
   * by default its zero unless its a value type and then will have its real value
   */
  double getValue();
  /*
   * return the symbol of the token.
   * by default it will be " ", if its a char type(operator for example) it will have its real symbol
   */
  char getSymbol();
  /*
   * return the precedence of the token, the precedence was sorted by the importance of an individual
   * token in the ShuntingYard algorithm.
   */
  double getPrecedence();
  /*
   * return if the token is a binary type, it will be only if its an operator type and
   * was declare binary
   */
  double isBinary();
  /*
   * return the string - parameter name.
   */
  string getParameter();
};

class Interpreter {
  unordered_map<string, Obj *> varObjMap;

 public:
  //constructor
  Interpreter(unordered_map<string, Obj *> &map) {
    this->varObjMap = map;
  }
  /*
   * get a string (expression line) and separate it to tokens and return a vector of them.
   */
  vector<string> separateS(string s);
/*
 *
 * interpret an expression given as a string and analyzed it and return its value
 * using ShuntingYard and RPN algorithm
 */
  Expression *interpret(string s);
  /*
   * function that perform the ShuntingYard algorithm, change the order from prefix
   * to postfix.
   */
  queue<Token *> ShuntingYard(vector<Token *> &tokens);
  /*
   * The function get tokens in postfix order and use the RPN algorithm to
   * return a mathematical expression
   */
  Expression *RPN(queue<Token *> &tokens);
  /*
   * delete all allocated memory of the structure given.
   */
  void deleteMemory(vector<Token *> &tokens, queue<Token *> &outputQueue, stack<Token *> &operatorStack);
  /*
   * delete all allocated memory in the queue.
   */
  void deleteMemory(queue<Token *> &outputQueue);

};

#endif //EX1__EX1_H_