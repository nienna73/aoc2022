#include "../getValuesFromFile.h"
#include "../split.h"
#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <unordered_set>


#define LINE_OF_INTEREST 2000000
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

int getManhattanDistance(long x1, long y1, long x2, long y2) {
    int part1 = abs(x1-x2);
    int part2 = abs(y1-y2);
    return part1 + part2;
}

void updateRange(long sensorX, long sensorY, long beaconX, long beaconY, vector<vector<char> > &vec, long line, long maxX, unordered_set<signed int> &xPosSeen) {
    int distance = getManhattanDistance(sensorX, sensorY, beaconX, beaconY);
    cout << "Distance to beacon: " << distance << endl;
    int distanceToTarget = getManhattanDistance(sensorX, sensorY, sensorX, line);
    cout << "Distance to line: " << distanceToTarget << endl;
    if (distanceToTarget > distance) {
        return;
    }
    // we're going to pass through the line of interest at some point
    // what will the xCoord be when we do so?
    int distanceToTargetLine = abs(sensorY - line);
    int spreadOfX = abs(distance - distanceToTargetLine);

    signed int index = sensorX;
    int row = abs(floor(index/ROW_SIZE)) +1;
    int spot = abs(index % ROW_SIZE);
    xPosSeen.insert(index);
    
    for (int i = 0; i <= spreadOfX; i++ ) {
        if (i == floor(spreadOfX / 2)) {
            cout << "passed halfway point" << endl;
        }
        index = sensorX + i;
        row = abs(floor(index/ROW_SIZE)) +1;
        spot = abs(index % ROW_SIZE);
        xPosSeen.insert(index);

        index = sensorX - i;
        row = abs(floor(index/ROW_SIZE))+1;
        spot = abs(index % ROW_SIZE);
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

    vector<vector<char>> vec(ceil(xCoordMax/ROW_SIZE) + BUFFER, vector<char> (ROW_SIZE, '.'));
    unordered_set<signed int> xPosSeen;
    // vector<bool> pointsTouched(xCoordMax + BUFFER, false);
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
                beaconX = stol(justX[0]); // + abs(xMin);
            }
            if (s.find('y') != doesNotExist) {
                vector<string> ySplit = splitString(s, '=');
                beaconY = stol(ySplit[1]); // + abs(yMin);
            }
        }
        for (string s : sensorSplit) {
            if (s.find('x') != doesNotExist) {
                vector<string> xSplit = splitString(s, '=');
                vector<string> justX = splitString(xSplit[1], ',');
                sensorX = stol(justX[0]); // + abs(xMin);
            }
            if (s.find('y') != doesNotExist) {
                vector<string> ySplit = splitString(s, '=');
                sensorY = stol(ySplit[1]); // + abs(yMin);
            }
        }
        if (beaconY == LINE_OF_INTEREST) {
            int row = abs(floor(beaconX / ROW_SIZE));;
            int spot = abs(beaconX % ROW_SIZE);
            xPosSeen.insert(beaconX);
        }
        if (sensorY == LINE_OF_INTEREST) {
            int row = abs(floor(sensorX / ROW_SIZE));
            int spot = abs(sensorX % ROW_SIZE);
            xPosSeen.insert(sensorX);
        }
        updateRange(sensorY, sensorX, beaconY, beaconX, vec, LINE_OF_INTEREST, xMax, xPosSeen);
        cout << "Finished: " << value << endl;

    }
    int ret = 0;
    for (signed int i : xPosSeen) {
        // cout << i << ", ";
        ret++;
    }
    cout << endl;
    cout << ret << endl;
    cout << xPosSeen.size() << endl;
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

    return 0;
}