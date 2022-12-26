#include "../getValuesFromFile.h"
#include "../split.h"
#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <unordered_set>


// #define LINE_OF_INTEREST 2000000
#define LINE_OF_INTEREST 10
#define BUFFER 1024
#define ROW_SIZE 512

tuple<long, long> getXBounds(vector<string> values) {
    long doesNotExist = string::npos;
    long maxX = 0;
    long minX = string::npos;
    for (string value : values) {
        vector<string> s = splitString(value, ' ');
        for (string v : s) {
            if (v.find('x') != doesNotExist) {
                vector<string> split = splitString(v, '=');
                string number = split[1];
                vector<string> numberAndComma = splitString(number, ',');
                long justTheNumber = stol(numberAndComma[0]);
                if (justTheNumber > maxX) {
                    maxX = justTheNumber;
                }
                if (justTheNumber < minX) {
                    minX = justTheNumber;
                }

            }
        }
    }
    return make_tuple(maxX, minX);
}

tuple<long, long> getYBounds(vector<string> values) {
    long doesNotExist = string::npos;
    long maxY = 0;
    long minY = string::npos;
    for (string value : values) {
        vector<string> s = splitString(value, ' ');
        for (string v : s) {
            if (v.find('y') != doesNotExist) {
                vector<string> split = splitString(v, '=');
                string number = split[1];
                vector<string> numberAndColon = splitString(number, ':');
                long justTheNumber = stol(numberAndColon[0]);
                if (justTheNumber > maxY) {
                    maxY = justTheNumber;
                }
                if (justTheNumber < minY) {
                    minY = justTheNumber;
                }

            }
        }
    }
    return make_tuple(maxY, minY);
}

long getManhattanDistance(long x1, long y1, long x2, long y2) {
    long part1 = abs(x1-x2);
    long part2 = abs(y1-y2);
    return part1 + part2;
}

void updateRange(long sensorX, long sensorY, long beaconX, long beaconY, unordered_set<signed int> &xPosSeen, unordered_set<signed int> beacons) {
    long distance = getManhattanDistance(sensorX, sensorY, beaconX, beaconY);
    cout << "Distance to beacon: " << distance << endl;
    long distanceToTarget = getManhattanDistance(sensorX, sensorY, sensorX, LINE_OF_INTEREST);
    cout << "Distance to line: " << distanceToTarget << endl;
    // if (distanceToTarget > distance) {
    //     return;
    // }
    // we're going to pass through the line of interest at some point
    // what will the xCoord be when we do so?
    long spreadOfX = distance - distanceToTarget;
    if (spreadOfX < 0 ) {
        return;
    }
    
    for (long i = spreadOfX * -1; i <= spreadOfX; i++ ) {
        long index = sensorX + i;
        xPosSeen.insert(index);

    }
    cout << "finished update" << endl;

}

vector<vector<char> > initializeMap(vector<string> values, tuple<long, long> xBounds, tuple<long, long> yBounds) {
    long xMax = get<0>(xBounds);
    long xMin = get<1>(xBounds);
    long yMax = get<0>(yBounds);
    long yMin = get<1>(yBounds);
    long xCoordMax = xMax - xMin;
    long yCoordMax = yMax - yMin;

    long doesNotExist = string::npos;

    vector<vector<char>> vec(ceil(xCoordMax/ROW_SIZE), vector<char> (ROW_SIZE, '.'));
    unordered_set<signed int> xPosSeen;
    unordered_set<signed int> beaconPos;

    for (string value : values) {
        vector<string> split = splitString(value, ':');
        string beacon = split[1];
        string sensor = split[0];
        vector<string> beaconSplit = splitString(beacon, ' ');
        vector<string> sensorSplit = splitString(sensor, ' ');
        long beaconX, beaconY, sensorX, sensorY;
        for (string s : beaconSplit) {
            if (s.find('x') != doesNotExist) {
                vector<string> xSplit = splitString(s, '=');
                vector<string> justX = splitString(xSplit[1], ',');
                beaconX = stol(justX[0]);
            }
            if (s.find('y') != doesNotExist) {
                vector<string> ySplit = splitString(s, '=');
                beaconY = stol(ySplit[1]);
            }
        }
        for (string s : sensorSplit) {
            if (s.find('x') != doesNotExist) {
                vector<string> xSplit = splitString(s, '=');
                vector<string> justX = splitString(xSplit[1], ',');
                sensorX = stol(justX[0]);
            }
            if (s.find('y') != doesNotExist) {
                vector<string> ySplit = splitString(s, '=');
                sensorY = stol(ySplit[1]);
            }
        }
        if (beaconY == LINE_OF_INTEREST) {
            beaconPos.insert(beaconX);
        }
        if (sensorY == LINE_OF_INTEREST) {
            beaconPos.insert(sensorX);
        }
        updateRange(sensorY, sensorX, beaconY, beaconX, xPosSeen, beaconPos);
        cout << "Finished: " << value << endl;

    }
    cout << endl;
    cout << beaconPos.size() << endl;
    cout << xPosSeen.size() - beaconPos.size() << endl;
    return vec;
}

int countChar(vector<char> s, char c) {
    int ret = 0;
    for (char a : s) {
        if (a == c) {
            ret += 1;
        }
    }
    return ret;
}


int main() {
    vector<string> values = getValuesFromFile("input.txt");
    tuple<long, long> xBounds = getXBounds(values);
    tuple<long, long> yBounds = getYBounds(values);
    vector<vector<char> > map = initializeMap(values, xBounds, yBounds);

    // int charCount = countChar(map[10 + (BUFFER/2) + abs(get<1>(xBounds))], '#');
    // cout << charCount << endl;
    // 198 is too low
    // 202 is too low
    // 5235789 is too high
    // 5779274
    // 5933076

    return 0;
}