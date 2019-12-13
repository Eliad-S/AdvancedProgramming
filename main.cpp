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
string splitVar(string s) {

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
            // read string in the parenthesis
            if ((*i)[j] == '"') {
                string s = "";
                j++;
                while ((*i)[j] != '"') {
                    s+=(*i)[j];
                    j++;
                }
                j++;
                s.substr(0, s.length() - 1);
                tokens.push_back(s);
                continue;
            }
            if ((*i)[j] == '=') {
                if (substr != "") {
                    tokens.push_back(substr);
                }
                tokens.push_back((*i).substr(j + 1, (*i).length()));
                break;
            }
            if (((*i)[j] == '(') || ((*i)[j] == ' ') || ((*i)[j] == ')') ||
                (*i)[j] == ',') {
                if (substr != "") {
                    tokens.push_back(substr);
                }
                substr = "";
            } else {
                substr += (*i)[j];
            }
            if (substr == "while" || substr == "if") {
                break;
            }
        }
    }
    for (auto f = tokens.begin(); f < tokens.end(); f++) {
        *f = removeSpace(*f);
        cout << *f << endl;
    }

    return 0;
}