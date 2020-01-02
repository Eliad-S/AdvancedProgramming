//
// Created by shirgold and EliadSellem on 25/12/2019.
//
#include "InterpreterFlight.h"
#include "Lexer.h"
#include "Parser.h"
int main(int argc, char *argv[]) {
    (void) argc;
    Lexer lexer(argv[1]);
    InterpreterFlight *interpreter_flight = InterpreterFlight::getInstance();
    interpreter_flight->setTokens(lexer.token);
    Parser* parser = new Parser(lexer.token);
    parser->interpret();
    InterpreterFlight::getInstance()->done();
    delete (parser);
    delete (InterpreterFlight::getInstance());
    return 0;
}
