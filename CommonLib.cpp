//
// Created by Ethan Edwards on 4/7/2023.
//

#include "CommonLib.h"

/*
 *  This function receives user arguments and assigns them to the ifstream and ofstream objects which manage I/O
 *  for the program. If the user supplies no arguments, this function tries to resolve the issue.
 *
 *  If the user has no input file available to pass, then they must enter ## when prompted to exit the program.
 */
void CommonLib::initFiles(ifstream& infile, ofstream& outfile, int argc, char* argv[], const string& progName){
    char confirm = 'n';
    string fname;
    // Check for inputs
    if (argc == 3){
        infile.open(argv[1]);
        outfile.open(argv[2]);
    }
    else if (argc == 2) {
        fname = argv[1];
        cout << "Found " << fname << " for input file. Continue using " << fname << " as input? (y/n) ";
        cin >> confirm;
        if (confirm == 'n') {
            cout << "Enter the new input filename: \n";
            cin >> fname;
        }
        infile.open(fname);
    }
    else {
        cout << "No input or output filename entered. Please run the program as" << progName << "<input file> <output file>\n";
        exit( EXIT_FAILURE);
    }

    // Confirm that the files are actually open & ask for reentry if not valid
    while (!outfile.is_open()){
        cout << "Please provide an existing filename to overwrite, or a new filename to create: ";
        cin >> fname;
        outfile = ofstream(fname, ios::out);
    }
    while (!infile.is_open() && fname != "##"){
        cout << "No input file found. Please provide a relative path and filename for an input file or enter ## to close the program: ";
        cin >> fname;
        infile.open(fname);
    }
}

/*
 *  This function reads a line of input from the input file and returns a vector of the values in the line.
 *  The function is templated to allow for any type of input.
 */
template <typename T>
vector<T> CommonLib::lineReader(int numInputs, char sep, ifstream& in){ // Template function to process n lines of input
    vector<T> inputs;
    string line;
    getline(in, line);
    for (int i = 0; i < numInputs; i++){
        // Adjusted processing for numbers
        if constexpr (is_same_v<T, int> || is_same_v<T, double> || is_same_v<T, float> || is_same_v<T, long> || is_same_v<T, long long> || is_same_v<T, short>){
            if (line.size() == 1) inputs.push_back(stoi(line.substr(0, line.size())));
            inputs.push_back(stoi(line.substr(0, line.find(sep))));
            line.erase(0, line.find(sep) + 1);
        } else if constexpr (is_same_v<T, string> || is_same_v<T, char>){ // Strings/chars
            if (line.size() == 1) inputs.push_back(line.substr(0, line.size()));
            inputs.push_back(line.substr(0, line.find(sep)));
            line.erase(0, line.find(sep) + 1);
        } else{ // This function can only handle standard datatypes at this time =(
            cout << "Invalid input type. Please use a valid type for the lineReader function.\n";
            exit( EXIT_FAILURE);
        }
    }
    return inputs;
}
