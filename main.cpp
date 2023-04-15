//
// Created by Joe Coon and Ethan Edwards on 4/14/23.
//

#include "CommonLib.h"
#include <iostream>
#include <tuple>

using namespace std;

enum { TWO = 2, ZED = 36 };

pair<int, int> findBasesIfMatch(const string& leftNumStr, const string& rightNumStr);

int main(int argc, char** argv) {
    ifstream infile; ofstream outfile;
    CommonLib::initFiles(infile, outfile, argc, argv);

    pair<int, int> bases;
    string left, right;

    infile >> left;
    infile >> right;

    while (!infile.eof()) {
        bases = findBasesIfMatch(left, right);
        if (bases.first && bases.second) {
            outfile << left << " (base " << bases.first << ") = "
                    << right << " (base " << bases.second << ")\n";
        }
        else {
            outfile << left << " is not equal to " << right << " in "
                    << "any base 2..36\n";
        }
        infile.ignore();
        infile >> left;
        infile >> right;
    }


    return 0;
}


pair<int, int> findBasesIfMatch(const string& leftNumStr, const string& rightNumStr) {

    auto binexp = [](long long base, long long exp) {
        long long res = 1;
        while (exp > 0) { // while exponent has not been shifted to 0
            if (exp & 1) // if the exponent is odd, multiply by base^0 for bit 0
                res = res * base;
            if (exp != 1)
                base = base * base; // square the base the same number of times as its set bit's positions
            exp >>= 1; // bit shift rightNum once and assign to exponent
        }
        return res;
    };

    auto charToLL = [](string number, int digitIndex)->long long {
        if (isalpha(number[digitIndex]))
            return toupper(number[digitIndex]) - 55; // ASCII 'A' is 65. Get 10 - 35 by subtracting 55 for all alpha chars.
        return number[digitIndex] - '0';
    };

    int leftNum, rightNum;
    bool skippedBase;

    for (int leftBase = TWO; leftBase <= ZED; leftBase++) {
        for (int rightBase = TWO; rightBase <= ZED; rightBase++) {
            leftNum = rightNum = 0; //reset values to accumulate
            skippedBase = false;
            for (int i = 0; i < leftNumStr.size(); i++) { // Calculate base 10 value of leftNum for comparison
                if (charToLL(leftNumStr, leftNumStr.size() - i - 1) >= leftBase) {
                    skippedBase = true;
                    break;
                }
                leftNum += charToLL(leftNumStr, leftNumStr.size() - i - 1) * binexp(leftBase, i);
            }
            for (int j = 0; j < rightNumStr.size(); j++) { // Calculate base 10 value of rightNum for comparison
                if (charToLL(rightNumStr, rightNumStr.size() - j - 1) >= rightBase) {
                    skippedBase = true;
                    break;
                }
                rightNum += charToLL(rightNumStr, rightNumStr.size() - j - 1) * binexp(rightBase, j);
            }
            if (leftNum == rightNum && !skippedBase)
                return { leftBase, rightBase };
        }
    }
    return { 0, 0 }; // Return 0 for both bases if there is no match
}

