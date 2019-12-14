//
// Created by eliadSellem on 11/4/19.
//

#include "ex1.h"
#include "Obj.h"

//calculate functions.

float Value::calculate() {
  return this->val;
}

float UPlus::calculate() {
  return this->exP->calculate();
}

float UMinus::calculate() {
  return this->exP->calculate() * -1;
}

float Plus::calculate() {
  return exP1->calculate() + exP2->calculate();
}

float Minus::calculate() {
  return exP1->calculate() - exP2->calculate();
}

float Mul::calculate() {
  return exP1->calculate() * exP2->calculate();
}

float Div::calculate() {
  if (this->exP2->calculate() == 0)
    throw "division by zero";
  else
    return this->exP1->calculate() / this->exP2->calculate();
}



//Token

//the method get vector of string that already splitted to tokens, and return vector of tokens
//that have the information about each individual tokens by enter its relevant fileds.
vector<Token *> Token::stringsToTokens(vector<string> vToken) {
  vector < Token * > tokens;
  regex isNum("^[0-9]+\\.?[0-9]*$");

  for (unsigned int i = 0; i < vToken.size(); i++) {
    Token *token = new Token();
    string sTok = vToken[i];
    //if the string represent a number
    if (regex_match(sTok.begin(), sTok.end(), isNum)) {
      token->value = stod(sTok);
      token->token_type = Number;
    } else {
      //if the string represent a left brace.
      if (sTok.compare("(") == 0) {
        token->token_type = LeftBrace;
      } else {
        //if the string represent a right brace.
        if (sTok.compare(")") == 0) {
          token->token_type = RightBrace;
        } else {
          //the string is an operator.
          const char op = sTok.at(0);

          switch (op) {
            //binary plus.
            case '+':token->token_type = Operator;
              token->symbol = '+';
              token->precedence = 10;
              token->binary = true;
              break;
              //unary plus
            case 'p':token->token_type = Operator;
              token->symbol = 'p';
              token->precedence = 30;
              token->binary = false;
              break;
              //binary minus.
            case '-':token->token_type = Operator;
              token->symbol = '-';
              token->precedence = 10;
              token->binary = true;
              break;
              //unary minus.
            case 'm':token->token_type = Operator;
              token->symbol = 'm';
              token->precedence = 30;
              token->binary = false;
              break;
            case '*':token->token_type = Operator;
              token->symbol = '*';
              token->precedence = 20;
              token->binary = true;
              break;
            case '/':token->token_type = Operator;
              token->symbol = '/';
              token->precedence = 20;
              token->binary = true;
              break;
            default:token->token_type = Variable;
              token->parameter = sTok;
          }
        }
      }
    }
    tokens.push_back(token);
  }
  return tokens;
}

double Token::getValue() {
  return this->value;
}
char Token::getSymbol() {
  return this->symbol;
}
double Token::getPrecedence() {
  return this->precedence;
}
double Token::isBinary() {
  return this->binary;
}
string Token::getParameter() {
  return this->parameter;
}

//Interpreter
vector<string> Interpreter::separateS(string s) {
  vector<string> subs;
  int operatorPlaces[6] = {0};
  string token;
  //find the closest operator or brace.
  while (s.length() != 0) {
    operatorPlaces[0] = s.find("+");
    operatorPlaces[1] = s.find("-");
    operatorPlaces[2] = s.find("*");
    operatorPlaces[3] = s.find("/");
    operatorPlaces[4] = s.find("(");
    operatorPlaces[5] = s.find(")");

    int min = s.length() - 1;
    for (int i = 0; i < 6; i++) {
      if ((operatorPlaces[i] != -1) && (operatorPlaces[i] < min)) {
        min = operatorPlaces[i];
      }
    }

    //next char is an operator;
    if (min == 0) {
      min++;
    }

    //if it is the first token or the previous token was "(", and the next token is + or -.
    //if we get true that's mean that its an Unary operator.
    if ((subs.size() == 0) || (subs[subs.size() - 1].compare("(") == 0)) {
      //change the unary operator to symbol that we will identify as unary at the future.
      if (s.substr(0, min).compare("+") == 0) {
        token = "p";
      } else {
        if (s.substr(0, min).compare("-") == 0) {
          token = "m";
        } else {
          token = s.substr(0, min);
        }
      }
    } else {
      token = s.substr(0, min);
    }

    s.erase(0, min);
    subs.push_back(token);
  }
  return subs;
}

void Interpreter::deleteMemory(vector<Token *> &tokens, queue<Token *> &outputQueue, stack<Token *> &operatorStack) {
  for (auto v: tokens) {
    delete (v);
  }

  while (!outputQueue.empty()) {
    delete (outputQueue.front());
    outputQueue.pop();
  }

  while (!operatorStack.empty()) {
    delete (operatorStack.top());
    operatorStack.pop();
  }
}

void Interpreter::deleteMemory(queue<Token *> &outputQueue) {
  while (!outputQueue.empty()) {
    delete (outputQueue.front());
    outputQueue.pop();
  }
}

queue<Token *> Interpreter::ShuntingYard(vector<Token *> &tokens) {
  unsigned int index = 0;
  std::queue < Token * > outputQueue;
  std::stack < Token * > operatorStack;

  while (index < tokens.size()) {
    Token *t = tokens[index];
    if ((t->token_type == Token::Number) || (t->token_type == Token::Variable)) {
      outputQueue.push(t);
      index++;
      continue;
    }
    if (t->token_type == Token::Operator) {
      if ((index == tokens.size() - 1) || (!t->isBinary() && tokens[index + 1]->token_type == Token::Variable)) {
        Interpreter::deleteMemory(tokens, outputQueue, operatorStack);
        throw "bad input";
      }
      while (operatorStack.size() != 0) {
        Token *oToken = operatorStack.top();
        if (oToken->token_type != Token::Operator) {
          break;
        }
        if (oToken->getPrecedence() >= t->getPrecedence()) {
          outputQueue.push(oToken);
          operatorStack.pop();
        } else {
          break;
        }
      }
      operatorStack.push(t);
      index++;
      continue;
    }
    if (t->token_type == Token::LeftBrace) {
      operatorStack.push(t);
      index++;
      continue;
    }
    if (t->token_type == Token::RightBrace) {
      while (operatorStack.size() != 0) {
        Token *oToken = operatorStack.top();
        if (oToken->token_type == Token::LeftBrace) {
          operatorStack.pop();
          delete (oToken);
          delete (t);
          break;
        } else {
          outputQueue.push(oToken);
          operatorStack.pop();
          if (operatorStack.size() == 0) {
            Interpreter::deleteMemory(tokens, outputQueue, operatorStack);
            throw "bad input";
          }
        }
      }
      index++;
      continue;
    }
  }
  while (operatorStack.size() != 0) {
    Token *oToken = operatorStack.top();
    if (oToken->token_type == Token::LeftBrace || oToken->token_type == Token::RightBrace) {
      Interpreter::deleteMemory(tokens, outputQueue, operatorStack);
      throw "bad input";
    }
    outputQueue.push(oToken);
    operatorStack.pop();
  }
  return outputQueue;
}

//this method split a string by the string we give it.
vector<string> Interpreter::splitSBy(string s, string delimiter) {
  vector<string> sVec;
  size_t pos = 0;
  std::string token;

  while (s.length() != 0) {
    pos = s.find(delimiter);
    //if the delimiter does not found in the string we change "pos" to the end of the string.
    if (pos >= s.length()) {
      pos = s.length();
      token = s.substr(0, pos);
      s.erase(0, pos);
    } else {
      //we to found the delimiter.
      token = s.substr(0, pos);
      s.erase(0, pos + delimiter.length());
    }

    sVec.push_back(token);
  }
  return sVec;
}

Expression *Interpreter::interpret(string s) {
  //separate the string given to relevant string parts
  vector<string> splittedParams = separateS(s);
  //take the previous vector and change it to Token's vector.
  vector < Token * > tokens = Token::stringsToTokens(splittedParams);
  //change to postfix.
  queue < Token * > postfixToken = ShuntingYard(tokens);
  //create an expresion using Reverse Polish notation algorithm.
  Expression *expression = RPN(postfixToken);
  return expression;
}

//create an expresion using Reverse Polish notation algorithm.
Expression *Interpreter::RPN(queue<Token *> &tokens) {
  std::stack < Expression * > stack;
  // empty expression.
  if (tokens.size() == 0) return nullptr;
  while (!tokens.empty()) {
    if (tokens.front()->token_type == Token::Number) {
      stack.push(new Value(tokens.front()->getValue()));
    } else {
      //find the key's value at our map and create a variable type.
      if (tokens.front()->token_type == Token::Variable) {
        int flag = 0;
        for (std::unordered_map<string, Obj*>::iterator it = this->varObjMap.begin(); it != this->varObjMap.end(); it++) {
          if (it->first.compare(tokens.front()->getParameter()) == 0) {
            stack.push(new Obj(it->first, it->second->getValue()));
            flag = 1;
            break;
          }
        }
        if (flag == 0) {
          Interpreter::deleteMemory(tokens);
          throw "illegal math expression";
        }
      } else {
        //it's an operator.
        if (tokens.front()->isBinary()) {
          // there are'nt enough for the operator.
          if (stack.size() < 2) {
            Interpreter::deleteMemory(tokens);
            throw "illegal math expression";
          }
          Expression *right = stack.top();
          stack.pop();
          Expression *left = stack.top();
          stack.pop();
          Expression *combine = nullptr;
          switch (tokens.front()->getSymbol()) {
            case '+':combine = new Plus(left, right);
              break;
            case '-':combine = new Minus(left, right);
              break;
            case '*':combine = new Mul(left, right);
              break;
            case '/':combine = new Div(left, right);
              break;
            default:break;
          }
          stack.push(combine);
        } else {
          //there is'nt an  expression in the stack.
          if (stack.size() == 0) {
            Interpreter::deleteMemory(tokens);
            throw "illegal math expression";
          }
          //unary
          Expression *unaryEx = stack.top();
          Expression *newEx = nullptr;
          stack.pop();
          switch (tokens.front()->getSymbol()) {
            case 'p':newEx = new UPlus(unaryEx);
              break;
            case 'm':newEx = new UMinus(unaryEx);
              break;
            default:break;
          }
          stack.push(newEx);
        }
      }
    }
    delete (tokens.front());
    tokens.pop();
  }
  if (stack.size() == 1) {
    return stack.top();
  } else {
    Interpreter::deleteMemory(tokens);
    throw "illegal math expression";
  }
}



