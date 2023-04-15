//
// Created by evane on 4/14/2023.
//

#ifndef UNTITLED_COMMONLIB_H
#define UNTITLED_COMMONLIB_H

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class CommonLib {
public:
    // Function to initialize input and output files
    static void initFiles(ifstream& infile, ofstream& outfile, int argc, char* argv[], const string& progName = "program");

    // Template function to process n lines of input
    template <typename T>
    vector<T> lineReader(int numInputs, char sep, ifstream& in);
};


#endif //UNTITLED_COMMONLIB_H
