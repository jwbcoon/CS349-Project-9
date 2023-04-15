//
// Created by Joe Coon and Ethan Edwards on 4/14/23.
//

#include "CommonLib.h"
#include <iostream>
#include <tuple>
#include <cmath>

using namespace std;

enum { ONE = 1, TWO = 2, THREE = 3, FOUR = 4, FIVE = 5, SIX = 6, SEVEN = 7, EIGHT = 8, NINE = 9,
    A = 10, B = 11, C = 12, D = 13, E = 14, F = 15, G = 16, H = 17, I = 18, J = 19, K = 20, L = 21, M = 22,
    N = 23, O = 24, P = 25, Q = 26, R = 27, S = 28, T = 29, U = 30, V = 31, W = 32, X = 33, Y = 34, Z = 35,
    ZED = 36 } Bases;

pair<int, int> findBasesIfMatch(int left, int right);

int main(int argc, char** argv) {
    ifstream infile; ofstream outfile;
    CommonLib::initFiles(infile, outfile, argc, argv);

    //do stuff
    int left = 12, right = 34;
    pair<int, int> bases = findBasesIfMatch(left, right);

    if (bases.first && bases.second) {
        cout << left << " (base " << bases.first << ") == "
             << right << " (base " << bases.second << ")\n";
    }
    else {
        cout << left << " is not equal to " << right << " in "
             << "any base 2..36\n";
    }

    return 0;
}


pair<int, int> findBasesIfMatch(int left, int right) {
    if (left == right) // check if values are equal in base 10
        return { A, A };

    auto binexp = [](long long base, long long exp) {
        long long res = 1;
        while (exp > 0) { // while exponent has not been shifted to 0
            if (exp & 1) // if the exponent is odd, multiply by base^0 for bit 0
                res = res * base;
            if (exp != 1)
                base = base * base; // square the base the same number of times as its set bit's positions
            exp >>= 1; // bit shift right once and assign to exponent
        }
        return res;
    };

    auto charToLL = [](char* number, int digitIndex) {
        return (long long)number[digitIndex] - '0';
    };

    int totDigsLeft = log10(left) + 1, totDigsRight = log10(right) + 1; // Calc length of string
    char leftDigits[totDigsLeft], rightDigits[totDigsRight]; // strings to store the digits of left and right inside
    bool skippedBase;
    itoa(left, leftDigits, A);
    itoa(right, rightDigits, A);

    for (int leftBase = ONE; leftBase <= ZED; leftBase++) {
        for (int rightBase = ONE; rightBase <= ZED; rightBase++) {
            left = right = 0; //reset values to accumulate
            skippedBase = false;
            for (int i = 0; i < totDigsLeft; i++) {
                if (charToLL(leftDigits, totDigsLeft - i - 1) >= leftBase) {
                    skippedBase = true;
                    break;
                }
                left += charToLL(leftDigits, totDigsLeft - i - 1) * binexp(leftBase, i);
            }
            for (int j = 0; j < totDigsRight; j++) {
                if (charToLL(rightDigits, totDigsRight - j - 1) >= rightBase) {
                    skippedBase = true;
                    break;
                }
                right += charToLL(rightDigits, totDigsRight - j - 1) * binexp(rightBase, j);
            }
            if (left == right && !skippedBase)
                return { leftBase, rightBase };
        }
    }
    return { 0, 0 }; // Return 0 for both bases if there is no match
}

