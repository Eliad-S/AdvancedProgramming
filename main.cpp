#include <iostream>
#include "InterpreterFlight.h"
#include "Lexer.h"
int main(int argc, char *argv[]) {
  ifstream inFile(argv[1], ios::in);
  Lexer lexer(argv[1]);
  InterpreterFlight *interpreter_flight = InterpreterFlight::getInstance();
  interpreter_flight->setTokens(lexer.token);
  interpreter_flight->parser();
  return 0;
}
