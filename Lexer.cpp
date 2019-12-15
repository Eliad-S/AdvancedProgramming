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
void splitVar(string s, vector<string> tokens) {
    tokens.push_back("var");
    int index = s.find("->");
    if (index < s.length()) {
        // name
        string name = s.substr(0, index - 1);
        // sim
        string sim = s.substr(index + 6, s.length() - 2); // check
        tokens.push_back(name);
        tokens.push_back("sim");
        tokens.push_back(sim);
    }
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
                splitVar(substr(*i, 4, (*i).length() - 1)) // check
            }
        }

    }
    for (auto f = tokens.begin(); f < tokens.end(); f++) {
        *f = removeSpace(*f);
        cout << *f << endl;
    }

    return 0;
}