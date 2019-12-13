#include <iostream>
#include "InterpreterFlight.cpp"
int main(int argc, char *argv[]) {
    ifstream inFile(argv[1], ios::in);
    InterpreterFlight iF(inFile);
    iF.parser();
    return 0;
}