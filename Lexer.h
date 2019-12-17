//
// Created by shirgold on 17/12/2019.
//

#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
class Lexer {
public:
    vector<string> token;
    Lexer(string fileName);
    string removeSpace(string str);
    string removeQuotatin(string str);
    void splitOther(string s, vector<string> *tokens);
    void splitVar(string s, vector<string> *tokens);
    void splitOpenDataServer(string s, vector<string> *tokens);
    void splitConnectControlClient(string s, vector<string> *tokens);
    void splitPrint(string s, vector<string> *tokens);
    void splitSleep(string s, vector<string> *tokens);
    void splitWhileOrIf(string s, vector<string> *tokens);
};
#ifndef ADVANCEDPROGRAMMING_LEXER_H
#define ADVANCEDPROGRAMMING_LEXER_H

#endif //ADVANCEDPROGRAMMING_LEXER_H
