//
// Created by shirgold and EliadSellem on 26/12/2019.
//

#ifndef ADVANCEDPROGRAMMING_PARSER_H
#define ADVANCEDPROGRAMMING_PARSER_H

#include <iostream>
#include <vector>

using namespace std;

class Parser {
    vector<string> array;
    int limit;
    int start;
public:
    Parser(int start1, int limit1, vector<string> arr) {
        this->array = arr;
        this->limit = limit1;
        this->start = start1;
    }

    Parser(vector<string> arr) {
        this->array = arr;
        this->limit = arr.size();
        this->start = 0;
    }

    /*
     * interpret the array by sorting the words to there relevant Command
     * that will be detected by our CommandMap, and execute the commands.
     */
    void interpret();

    ~Parser() {}
};


#endif //ADVANCEDPROGRAMMING_PARSER_H
