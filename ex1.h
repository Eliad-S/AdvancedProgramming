//
// Created by eliadsellem on 11/4/19.
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
    Value(float v) : val(v) {}
    float calculate() override;
};

class UnaryOperator : public Expression {
protected:
    Expression *exP{nullptr};
public:
    UnaryOperator(Expression *exp) {
        this->exP = exp;
    }
    ~UnaryOperator() {
        delete (exP);
    }
};

class UPlus : public UnaryOperator {

public:
    UPlus(Expression *exp) : UnaryOperator(exp) {};

    float calculate() override;
};

class UMinus : public UnaryOperator {
public:
    UMinus(Expression *exp) : UnaryOperator(exp) {}
    float calculate();

};

class BinaryOperator : public Expression {
protected:
    Expression *exP1{nullptr};
    Expression *exP2{nullptr};
    BinaryOperator(Expression *exp1, Expression *exp2) : exP1(exp1), exP2(exp2) {}

public:
    ~BinaryOperator() {
        delete (exP1);
        delete (exP2);
    }
};

class Plus : public BinaryOperator {
public:
    Plus(Expression *exp1, Expression *exp2) : BinaryOperator(exp1, exp2) {}

    float calculate() override;
};

class Minus : public BinaryOperator {
public:
    Minus(Expression *exp1, Expression *exp2) : BinaryOperator(exp1, exp2) {}

    float calculate() override;
};

class Mul : public BinaryOperator {
public:
    Mul(Expression *exp1, Expression *exp2) : BinaryOperator(exp1, exp2) {}

    float calculate() override;
};

class Div : public BinaryOperator {
public:
    Div(Expression *exp1, Expression *exp2) : BinaryOperator(exp1, exp2) {}
    float calculate() override;
};

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

    static vector<Token *> stringsToTokens(vector<string> vToken);

    double getValue();
    char getSymbol();
    double getPrecedence();
    double isBinary();
    string getParameter();
};

class Interpreter {
    unordered_map<string, Obj*> varObjMap;

public:

    Interpreter(unordered_map<string, Obj*> &map) {
        this->varObjMap = map;
    }
    vector<string> separateS(string s);

    Expression *interpret(string s);

    queue<Token *> ShuntingYard(vector<Token *> &tokens);

    Expression *RPN(queue<Token *> &tokens);

    vector<string> splitSBy(string s, string delimiter);

    void deleteMemory(vector<Token *> &tokens,queue<Token *> &outputQueue,stack<Token *> &operatorStack);

    void deleteMemory(queue<Token *> &outputQueue);

};

#endif //EX1__EX1_H_