//
// Created by shirgold and EliadSellem on 25/12/2019.
//

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Lexer {
public:
    vector<string> token;

    Lexer(string fileName);
    /*
     * removes spaces from given string and returns it.
     */
    string removeSpace(string str);
    /*
     * removes - ",(,) - from given string and returns it.
     */
    string removeQuotatin(string str);
    /*
     * splits lines of update object or call to function.
     */
    void splitOther(string s, vector<string> *tokens);
    /*
     * splits lines that contains declaration of new variable.
     */
    void splitVar(string s, vector<string> *tokens);
    /*
     * splits line that contain "openDataServer".
     */
    void splitOpenDataServer(string s, vector<string> *tokens);
    /*
     * splits line that contain "openControlClient".
     */
    void splitConnectControlClient(string s, vector<string> *tokens);
    /*
     * splits lines that contains "print".
     */
    void splitPrint(string s, vector<string> *tokens);
    /*
     * splits lines that contains "sleep".
     */
    void splitSleep(string s, vector<string> *tokens);
    /*
     * split lines that contains "while" or "if".
     */
    void splitWhileOrIf(string s, vector<string> *tokens);
    /*
     * split lines that contains declaration of function.
     */
    void splitFunc(string basicString, vector<string> *pVector);
};

#ifndef ADVANCEDPROGRAMMING_LEXER_H
#define ADVANCEDPROGRAMMING_LEXER_H

#endif //ADVANCEDPROGRAMMING_LEXER_H
