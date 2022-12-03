#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <map>
using namespace std;

int main() {
    fstream input;
    input.open("input.txt");

    vector<string> values;

    if (input.is_open()) {
        string val;
        while (getline(input, val)) {
            values.push_back(val);
        }
    }
    input.close();

    map<char, int> movesToValue;

    movesToValue['X'] = 0;
    movesToValue['Y'] = 3;
    movesToValue['Z'] = 6;

    long int score = 0;

    for (string &line : values) {
        char oponent = line[0];
        char outcome = line[2];
        if (outcome == 'X') {
            if (oponent == 'A') {
                score = score + 3;
            } else if (oponent == 'B') {
                score = score + 1;
            } else {
                score = score + 2;
            }
        } else if (outcome == 'Y') {
            if (oponent == 'A') {
                score = score + 1;
            } else if (oponent == 'B') {
                score = score + 2;
            } else {
                score = score + 3;
            }
        } else if (outcome == 'Z') {
            if (oponent == 'A') {
                score = score + 2;
            } else if (oponent == 'B') {
                score = score + 3;
            } else {
                score = score + 1;
            }
        }
        
        score = score + movesToValue[outcome];
    }

    cout << score << endl;
    return 0;
}