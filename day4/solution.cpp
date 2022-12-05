#include "../getValuesFromFile.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

vector<string> split(string line, char delim) {
    vector<string> ret;
    string part;
    for (char &c : line) {
        if (c == delim) {
            ret.push_back(part);
            part = "";
        } else {
            part += c;
        }
    }

    ret.push_back(part);

    return ret;
}


int main() {
    vector<string> myValues = getValuesFromFile("input.csv");

    long int doesNotExist = string::npos;
    int totalPart1 = 0;
    int totalPart2 = 0;
    for (string &line : myValues) {
        vector<string> parts = split(line, ',');
        vector<string> part1 = split(parts[0], '-');
        vector<string> part2 = split(parts[1], '-');
        int part1Start = stoi(part1[0]);
        int part1End = stoi(part1[1]);
        int part2Start = stoi(part2[0]);
        int part2End = stoi(part2[1]);

        // part 1
        if (part1Start <= part2Start && part1End >= part2End) {
            totalPart1 += 1;
        } else if (part2Start <= part1Start && part2End >= part1End) {
            totalPart1 += 1;
        }

        // part 2
        if (part1Start >= part2Start && part1Start <= part2End) {
            // the case where part 1 starts somewhere in part 2
            totalPart2 += 1;
        } else if (part1End >= part2Start && part1End <= part2End) {
            // part 1 ends somewhere in part 2
            totalPart2 += 1;
        } else if (part2Start >= part1Start && part2Start <= part1End) {
            // part 2 starts somewhere in part 1
            totalPart2 += 1;
        } else if (part2End >= part1Start && part2End <= part1End) {
            // part 2 ends somewhere in part 1
            totalPart2 += 1;
        }

    }

    cout << totalPart2 << endl;

    return 0;
}