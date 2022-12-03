#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main() {
    fstream myfile;
    myfile.open("input.txt", ios::in);

    vector<string> values;

    if (myfile.is_open()) {
        string val;
        while(getline(myfile, val)) {
            values.push_back(val);
            // cout << val << endl;
        }
    }

    myfile.close();
    long int max = 0;
    long int value = 0;
    vector<long int> caloric_values;

    for (string &line : values ) {
        if (line != "") {
            value = value + stoi(line);
        } else {
            if (value > max) {
                max = value;
            }
            caloric_values.push_back(value);
            value = 0;
        }
    }

    sort(caloric_values.begin(), caloric_values.end(), greater<long int>());

    long int top_three = caloric_values[0] + caloric_values[1] + caloric_values[2];
    cout << top_three << endl;
    return max;
}