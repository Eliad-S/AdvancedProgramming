#include <iostream>
#include <vector>
#include "Lexer.h"

using namespace std;

Lexer::Lexer(string fileName) {
    ifstream in(fileName);
    string str;
    vector<string> lines;
    // read lines
    while (getline(in, str)) {
        lines.push_back(str);
    }
    string substr = "";
    vector<string> tokens;
    for (auto i = lines.begin(); i < lines.end(); i++) {
        for (unsigned int j = 0; j < (*i).length(); j++) {
            if (substr == "var") {
                string withoutSpaces =
                        removeSpace((*i).substr(4, (*i).length() - 1));
                splitVar(withoutSpaces, &tokens); // check
                substr = "";
                break;
            }
            if (substr == "openDataServer") {
                string withoutSpaces =
                        removeSpace((*i).substr(14, (*i).length() - 1));
                splitOpenDataServer(withoutSpaces, &tokens);
                substr = "";
                break;
            }
            if (substr == "connectControlClient") {
                string withoutSpaces =
                        removeSpace((*i).substr(20, (*i).length() - 1));
                splitConnectControlClient(withoutSpaces, &tokens);
                substr = "";
                break;
            }
            if (substr == "Sleep") {
                string withoutSpaces =
                        removeSpace((*i).substr(j, (*i).length() - 1));
                splitSleep(withoutSpaces, &tokens);
                substr = "";
                break;
            }
            if (substr == "Print") {
                splitPrint((*i).substr(j, (*i).length() - 1), &tokens);
                substr = "";
                break;
            }
            if (substr == "while") {
                tokens.push_back("while");
                string withoutSpaces =
                        removeSpace((*i).substr(j, (*i).length() - 1));
                splitWhileOrIf(withoutSpaces, &tokens);
                substr = "";
                break;
            }
            if (substr == "if") {
                tokens.push_back("if");
                string withoutSpaces =
                        removeSpace((*i).substr(2, (*i).length() - 1));
                splitWhileOrIf(withoutSpaces, &tokens);
                substr = "";
                break;
            }
            if ((*i)[j] == '}') {
                tokens.push_back("}");
                substr = "";
                break;
            }
            if (substr == " " || substr == "\t") {
                substr = "";
            }
            if ((*i)[j] == '{') {
                splitFunc(substr, &tokens);
                substr = "";
                break;
            }
            substr += (*i)[j];
            // variable assignment
            if (j == (*i).length() - 1) {
                splitOther(substr, &tokens);
                substr = "";
            }
        }
    }
    this->token = tokens;
    in.close();
}

string Lexer::removeSpace(string str) {
    string dest = "";
    for (unsigned int i = 0; i < str.length(); ++i) {
        if (str[i] != ' ') {
            dest += str[i];
        }
    }
    return dest;
}

string Lexer::removeQuotatin(string str) {
    string dest = "";
    for (unsigned int i = 0; i < str.length(); ++i) {
        if (str[i] != '"' && str[i] != ')' && str[i] != '(') {
            dest += str[i];
        }
    }
    return dest;
}

void Lexer::splitOther(string s, vector<string> *tokens) {
    s = removeSpace(s);
    unsigned int index;
    string name;
    index = s.find("+=");
    if (index < s.length()) {
        tokens->push_back("obj");
        name = s.substr(0, index);
        tokens->push_back(s.substr(0, index));
        tokens->push_back("=");
        // var = var + expression
        tokens->push_back
                (name + "+(" + s.substr(index + 2, s.length() - 1) + ")");
        return;
    }
    index = s.find("-=");
    if (index < s.length()) {
        tokens->push_back("obj");
        name = s.substr(0, index);
        tokens->push_back(s.substr(0, index));
        tokens->push_back("=");
        // var = var - expression
        tokens->push_back
                (name + "-(" + s.substr(index + 2, s.length() - 1) + ")");
        return;
    }
    index = s.find("*=");
    if (index < s.length()) {
        tokens->push_back("obj");
        name = s.substr(0, index);
        tokens->push_back(s.substr(0, index));
        tokens->push_back("=");
        // var = var * expression
        tokens->push_back
                (name + "*(" + s.substr(index + 2, s.length() - 1) + ")");
        return;
    }
    index = s.find("/=");
    if (index < s.length()) {
        tokens->push_back("obj");
        name = s.substr(0, index);
        tokens->push_back(s.substr(0, index));
        tokens->push_back("=");
        // var = var / expression
        tokens->push_back
                (name + "/(" + s.substr(index + 2, s.length() - 1) + ")");
        return;
    }
    index = s.find("=");
    if (index < s.length()) {
        tokens->push_back("obj");
        tokens->push_back(s.substr(0, index));
        tokens->push_back("=");
        tokens->push_back(s.substr(index + 1, s.length() - 1));
        return;
    }
    index = s.find("(");
    if (index < s.length()) {
        tokens->push_back("Func");
        // name
        tokens->push_back(s.substr(0, index));
        s = removeQuotatin(s.substr(index));
        // parameter
        tokens->push_back(s);
    }
}

void Lexer::splitVar(string s, vector<string> *tokens) {
    tokens->push_back("var");
    string name;
    unsigned int index = s.find("->");
    if (index < s.length()) {
        // name
        name = s.substr(0, index);
        tokens->push_back(name);
        tokens->push_back("->");
    } else {
        index = s.find("<-");
        // new var without sim
        if (index >= s.length()) {
            index = s.find("=");
            if (index < s.length()) {
                tokens->push_back(s.substr(0, index));
                tokens->push_back("=");
                tokens->push_back(s.substr(index + 1, s.length() - 1));
            }
            return;
        } else {
            // name
            name = s.substr(0, index);
            tokens->push_back(name);
            tokens->push_back("<-");
        }
    }
    // sim
    string sim = removeQuotatin(s.substr(index + 6, s.length())); // check
    tokens->push_back("sim");
    tokens->push_back(sim);
}

void Lexer::splitOpenDataServer(string s, vector<string> *tokens) {
    tokens->push_back("openDataServer");
    int startIndex = s.find("(");
    int endIndex = s.find(")");
    tokens->push_back(s.substr(startIndex + 1, endIndex - 1)); // check
}

void Lexer::splitConnectControlClient(string s, vector<string> *tokens) {
    tokens->push_back("connectControlClient");
    int startIndex = s.find("(");
    int endIndex = s.find(")");
    string withoutQuotatin =
            removeQuotatin(s.substr(startIndex + 1, endIndex - 1));
    int indexComma = withoutQuotatin.find(",");
    // IP
    tokens->push_back(withoutQuotatin.substr(0, indexComma));
    // port
    tokens->push_back(withoutQuotatin.substr(indexComma + 1,
                                             withoutQuotatin.length() - 1));
}

void Lexer::splitPrint(string s, vector<string> *tokens) {
    tokens->push_back("Print");
    tokens->push_back(s.substr(1, s.length() - 2));
}

void Lexer::splitSleep(string s, vector<string> *tokens) {
    tokens->push_back("Sleep");
    tokens->push_back(removeQuotatin(s));
}

void Lexer::splitWhileOrIf(string s, vector<string> *tokens) {
    if (s[0] == '(' && s[s.length() - 1] == ')') {
        s = s.substr(1, s.length() - 2);
    }
    s = removeSpace(s);
    unsigned int index;
    index = s.find("==");
    if (index < s.length()) {
        // expression 1
        tokens->push_back(s.substr(0, index));
        tokens->push_back("==");
        // expression 2
        tokens->push_back(s.substr(index + 2, s.length() - index - 3));
        goto end;
    }
    index = s.find("<=");
    if (index < s.length()) {
        // expression 1
        tokens->push_back(s.substr(0, index));
        tokens->push_back("<=");
        // expression 2
        tokens->push_back(s.substr(index + 2, s.length() - index - 3));
        goto end;
    }
    index = s.find(">=");
    if (index < s.length()) {
        // expression 1
        tokens->push_back(s.substr(0, index));
        tokens->push_back(">=");
        // expression 2
        tokens->push_back(s.substr(index + 2, s.length() - index - 3));
        goto end;
    }
    index = s.find(">");
    if (index < s.length()) {
        // expression 1
        tokens->push_back(s.substr(0, index));
        tokens->push_back(">");
        // expression 2
        tokens->push_back(s.substr(index + 1, s.length() - index - 2));
        goto end;
    }
    index = s.find("<");
    if (index < s.length()) {
        // expression 1
        tokens->push_back(s.substr(0, index));
        tokens->push_back("<");
        // expression 2
        tokens->push_back(s.substr(index + 1, s.length() - index - 2));
        goto end;
    } else {
        tokens->push_back(s.substr(0, s.length() - 2));
    }
    end:
    tokens->push_back("{");
}

void Lexer::splitFunc(string s, vector<string> *tokens) {
    tokens->push_back("NewFunc");
    int index = s.find('(');
    string nameFunc = s.substr(0, index);
    s = s.substr(index + 1);
    s = removeQuotatin(s);
    index = s.find(' ');
    string type = s.substr(0, index);
    string name = s.substr(index + 1, s.length() - index - 2);
    tokens->push_back(nameFunc);
    tokens->push_back(type);
    tokens->push_back(name);
    tokens->push_back("{");
}
