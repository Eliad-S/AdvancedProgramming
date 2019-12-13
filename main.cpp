//#include <iostream>
//#include "InterpreterFlight.cpp"
//int main(int argc, char *argv[]) {
//    ifstream inFile(argv[1], ios::in);
//    InterpreterFlight iF(inFile);
//    iF.parser();
//    return 0;
//}

#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
string removeSpace(string str) {
    string dest = "";
    for (int i = 0; i < str.length(); ++i)
        if (str[i] != ' ') {
            dest += str[i];
        }
    return dest;
}
string removeQuotatin(string str) {
    string dest = "";
    for (int i = 0; i < str.length(); ++i)
        if (str[i] != '"' && str[i] != ')' ) {
            dest += str[i];
        }
    return dest;
}
void splitVar(string s, vector<string> *tokens) {
    string name;
    tokens->push_back("var");
    int index = s.find("->");
    if (index < s.length()) {
        // name
        name = s.substr(0, index);
    } else {
        index = s.find("<-");
        // name
        name = s.substr(0, index);
    }
    // sim
    string sim = removeQuotatin(s.substr(index + 6, s.length())); // check
    tokens->push_back(name);
    tokens->push_back("sim");
    tokens->push_back(sim);
}
void splitOpenDataServer(string s, vector<string> *tokens) {
    tokens->push_back("openDataServer");
    int startIndex = s.find("(");
    int endIndex = s.find(")");
    tokens->push_back(s.substr(startIndex + 1, endIndex - 1)); // check
}
void splitConnectControlClient(string s, vector<string> *tokens) {
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
int main(int argc, char* argv[]) {
    ifstream in("file.txt");
    string str;
    vector<string> lines;
    // read lines
    while (getline(in, str)) {
        lines.push_back(str);
    }
    string substr = "";
    vector<string> tokens;
    for(auto i = lines.begin(); i < lines.end(); i++) {
        for (int j = 0; j < (*i).length();j++) {
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
            substr += (*i)[j];
        }
    }
    for (auto f = tokens.begin(); f < tokens.end(); f++) {
        cout << *f << endl;
    }

    return 0;
}