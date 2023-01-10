#include "../getValuesFromFile.h"
#include "../split.h"
#include <vector>
#include <string>
#include <iostream>

// referencing : https://github.com/vss2sn/advent_of_code/blob/master/2022/cpp/day_13a.cpp

vector<string> removeBlankLines(vector<string> input) {
    vector<string> ret;
    for (string s : input) {
        if (s.size()) {
            ret.push_back(s);
        }
    }
    return ret;
}

bool isNumber(char c) {
    string s = "0123456789";
    return s.find(c) != string::npos;
}


vector<tuple<int, bool> > getOrders(vector<string> values) {
    vector<tuple<int, bool> > ret;
    int j = 0;
    int index = 1;
    string part1 = "";
    string part2 = "";
    while (j < values.size()) {
        if (values[j] != "" && part1 == "") {
            part1 = values[j];
            j++;
            continue;
        } else if (values[j] != "" && part2 == "") {
            part2 = values[j];
            j++;
        } else if (values[j] == "") {
            part1 = "";
            part2 = "";
            j++;
            continue;
        }
        // cout << part1 << ", " << part2 << endl;
        int i1 = 0;
        int i2 = 0;
        bool found = false;
        while (i1 < part1.length() && i2 < part2.length() && !found) {
            int n1 = 0;
            while (isNumber(part1[i1])) {
                n1 = n1 * 10 + (int) part1[i1];
                i1++;
            }
            int n2 = 0;
            while (isNumber(part2[i2])) {
                n2 = n2*10 + (int) part2[i2];
                i2++;
            }

            if (n1 == n2 && n1 != 0) {
                // packets are equal so far
                continue;
            } else if (n1 < n2) {
                // packets are in right order
                tuple<int, bool> r = make_tuple(index, true);
                ret.push_back(r);
                found = true;
            } else if (n1 > n2) {
                // packets are in wrong order
                tuple<int, bool> r = make_tuple(index, false);
                ret.push_back(r);
                found = true;
            } else if (part1[i1] == part2[i2]) {
                i1++;
                i2++;
            } else if (part1[i1] == ']') {
                // packets are in right order
                tuple<int, bool> r = make_tuple(index, true);
                ret.push_back(r);
                found = true;
            } else if (part1[i1] == '[' || part1[i1] == ',') {
                i1++;
            } else if (part2[i2] == '[' || part2[i2] == ',') {
                i2++;
            }
        }
        if (i1 == part1.length() && !found) {
            // packets are in right order
            tuple<int, bool> r = make_tuple(index, true);
            ret.push_back(r);
        } else if (!found) {
            tuple<int, bool> r = make_tuple(index, false);
            ret.push_back(r);
            i1 = part1.length();
        }
        index++;
    }
    return ret;
    
}

int getSumPairsInRightOrder(vector<tuple<int, bool> > inOrder) {
    int ret = 0;
    for (tuple<int, bool> t : inOrder) {
        if (get<1>(t)) {
            cout << "Pair " << get<0>(t) << " is in right order" << endl;
            ret += get<0>(t);
        }
    }
    return ret;
}


int main() {
    vector<string> values = getValuesFromFile("input.txt");
    // values = removeBlankLines(values);
    vector<tuple<int, bool> > inOrder = getOrders(values);
    int sum = getSumPairsInRightOrder(inOrder);
    cout << "Sum: " << sum << endl;
    return 0;
    // Part 1:
    // 2856 is too low
    // 5611 is too low
    // 5722 is too low
    // 5810 is wrong
    // 6208 is wrong
    // 6388 is wrong
    // 5892 is wrong
    // 5825 is wrong
    // 5552 is wrong
}