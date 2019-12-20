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
        for(auto i = lines.begin(); i < lines.end(); i++) {
            for (int j = 0; j < (*i).length(); j++) {
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
                            removeSpace((*i).substr(5, (*i).length() - 1));
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
                substr += (*i)[j];
                if (j == (*i).length() - 1) {
                    splitOther(substr, &tokens);
                    substr = "";
                }
            }
        }
        this->token = tokens;
    }
string Lexer:: removeSpace(string str) {
        string dest = "";
        for (int i = 0; i < str.length(); ++i)
            if (str[i] != ' ') {
                dest += str[i];
            }
        return dest;
    }
string Lexer:: removeQuotatin(string str) {
        string dest = "";
        for (int i = 0; i < str.length(); ++i)
            if (str[i] != '"' && str[i] != ')' && str[i] != '(') {
                dest += str[i];
            }
        return dest;
    }
void Lexer:: splitOther(string s, vector<string> *tokens) {
    tokens->push_back("obj");
    s = removeSpace(s);
    int index;
    string name;
    index = s.find("+=");
    if (index < s.length()) {
        name = s.substr(0, index);
        tokens->push_back(s.substr(0, index));
        tokens->push_back("=");
        tokens->push_back
                (name + "+(" + s.substr(index + 2, s.length() - 1) + ")");
        return;
    }
    index = s.find("-=");
    if (index < s.length()) {
        name = s.substr(0, index);
        tokens->push_back(s.substr(0, index));
        tokens->push_back("=");
        tokens->push_back
                (name + "-(" + s.substr(index + 2, s.length() - 1) + ")");
        return;
    }
    index = s.find("*=");
    if (index < s.length()) {
        name = s.substr(0, index);
        tokens->push_back(s.substr(0, index));
        tokens->push_back("=");
        tokens->push_back
                (name + "*(" + s.substr(index + 2, s.length() - 1) + ")");
        return;
    }
    index = s.find("/=");
    if (index < s.length()) {
        name = s.substr(0, index);
        tokens->push_back(s.substr(0, index));
        tokens->push_back("=");
        tokens->push_back
                (name + "/(" + s.substr(index + 2, s.length() - 1) + ")");
        return;
    }
    index = s.find("=");
    if (index < s.length()) {
        tokens->push_back(s.substr(0, index));
        tokens->push_back("=");
        tokens->push_back(s.substr(index + 1, s.length() - 1));
        return;
    }
}
void Lexer:: splitVar(string s, vector<string> *tokens) {
        tokens->push_back("var");
        string name;
        int index = s.find("->");
        if (index < s.length()) {
            // name
            name = s.substr(0, index);
            tokens->push_back(name);
            tokens->push_back("->");
        } else {
            index = s.find("<-");
            if (index >= s.length())  {
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
void Lexer:: splitOpenDataServer(string s, vector<string> *tokens) {
        tokens->push_back("openDataServer");
        int startIndex = s.find("(");
        int endIndex = s.find(")");
        tokens->push_back(s.substr(startIndex + 1, endIndex - 1)); // check
    }
void Lexer:: splitConnectControlClient(string s, vector<string> *tokens) {
        tokens->push_back("connectControlClient");
        int startIndex = s.find("(");
        int endIndex = s.find(")");
        string withoutQuotatin =
                removeQuotatin(s.substr(startIndex + 1, endIndex - 1));
        int indexComma = withoutQuotatin.find(",");
        tokens->push_back(withoutQuotatin.substr(0, indexComma));
        tokens->push_back(withoutQuotatin.substr(indexComma + 1,
                                                 withoutQuotatin.length() - 1));
    }
void Lexer:: splitPrint(string s, vector<string> *tokens) {
        tokens->push_back("Print");
        tokens->push_back(removeQuotatin(s.substr(1, s.length() - 1)));
    }
void Lexer:: splitSleep(string s, vector<string> *tokens) {
        tokens->push_back("Sleep");
        tokens->push_back(removeQuotatin(s));
    }
void Lexer:: splitWhileOrIf(string s, vector<string> *tokens) {
        if (s[0] == '(' && s[s.length() - 1] == ')') {
            s = s.substr(1, s.length() - 2); // check
        }
        s = removeSpace(s);
        int index;
        index = s.find("==");
        if (index < s.length()) {
            tokens->push_back(s.substr(0, index));
            tokens->push_back("==");
            tokens->push_back(s.substr(index + 2, s.length() - index - 2));
            cout << s << " " << s.length() << endl;
            goto end;
        }
        index = s.find("<=");
        if (index < s.length()) {
            tokens->push_back(s.substr(0, index));
            tokens->push_back("<=");
            tokens->push_back(s.substr(index + 2, s.length() - index - 2));
            goto end;
        }
        index = s.find(">=");
        if (index < s.length()) {
            tokens->push_back(s.substr(0, index));
            tokens->push_back(">=");
            tokens->push_back(s.substr(index + 2, s.length() - index - 2));
            goto end;
        }
        index = s.find(">");
        if (index < s.length()) {
            tokens->push_back(s.substr(0, index));
            tokens->push_back(">");
            tokens->push_back(s.substr(index + 1, s.length() - index - 2));
            goto end;
        }
        index = s.find("<");
        if (index < s.length()) {
            tokens->push_back(s.substr(0, index));
            tokens->push_back("<");
            tokens->push_back(s.substr(index + 1, s.length() - index - 2));
            goto end;
        } else {
            tokens->push_back(s.substr(0, s.length() - 2));
        }
        end:
        tokens->push_back("{");
    }