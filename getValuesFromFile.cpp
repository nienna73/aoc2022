#include "getValuesFromFile.h"
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

vector<string> getValuesFromFile(string filename) {
    fstream input;
    input.open(filename);

    vector<string> myValues;

    if (input.is_open()) {
        string val;
        while (getline(input, val)) {
            myValues.push_back(val);
        }
    }

    input.close();
    return myValues;
}
