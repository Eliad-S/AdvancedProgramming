//
// Created by shirgold and EliadSellem on 26/12/2019.
//
#include "InterpreterFlight.h"
#include "Lexer.h"
#include "Parser.h"

int main(int argc, char *argv[]) {
    (void) argc;
    Lexer *lexer;
    try {
        lexer = new Lexer(argv[1]);
    } catch (const char *e) {
        cout << e << endl;
        return 0;
    }
    InterpreterFlight *interpreter_flight = InterpreterFlight::getInstance();
    interpreter_flight->setTokens(lexer->token);
    Parser *parser = new Parser(lexer->token);
    parser->interpret();
    InterpreterFlight::getInstance()->done();
    delete (InterpreterFlight::getInstance());
    delete (parser);
    delete (lexer);
    return 0;
}
