#include "../getValuesFromFile.h"
#include "../split.h"
#include <vector>
#include <string>
#include <iostream>

string removeChar(string s, char c) {
    string ret = "";
    for (char a : s) {
        if (a != c) {
            ret += a;
        }
    }
    return ret;
}

int findMaxX(vector<string> input) {
    int maxX = 0;
    for(string s : input) {
        vector<string> splitS = splitString(s, '-');
        for (string t : splitS) {
            vector<string> u = splitString(t, '>');
            for (string v : u) {
                vector<string> w = splitString(v, ',');
                if (w.size() == 2) {
                    if (stoi(w[1]) > maxX) {
                        maxX = stoi(w[1]);
                    }
                }
            }
        }
    }
    return maxX;
}

int findMaxY(vector<string> input) {
    int maxY = 0;
    for(string s : input) {
        vector<string> splitS = splitString(s, '-');
        for (string t : splitS) {
            vector<string> u = splitString(t, '>');
            for (string v : u) {
                vector<string> w = splitString(v, ',');
                if (w.size() == 2) {
                    if (stoi(w[0]) > maxY) {
                        maxY = stoi(w[0]);
                    }
                }
            }
        }
    }
    return maxY;
}

int findMinY(vector<string> input) {
    int minY = 100000;
    for(string s : input) {
        vector<string> splitS = splitString(s, '-');
        for (string t : splitS) {
            vector<string> u = splitString(t, '>');
            for (string v : u) {
                vector<string> w = splitString(v, ',');
                if (w.size() == 2) {
                    if (stoi(w[0]) < minY) {
                        minY = stoi(w[0]);
                    }
                }
            }
        }
    }
    return minY;
}

#define Y_BUFFER 512

vector<vector<char> > initializeMap(vector<string> input) {
    int maxX = findMaxX(input);
    int maxY = findMaxY(input) + Y_BUFFER; // make it much longer for part 2
    int minY = findMinY(input) - Y_BUFFER;
    cout << maxX << ", " << maxY << ", " << minY << endl;
    vector<vector<char> > map;
    for (int i = 0; i <= maxX; i++) {
        vector<char> vec;
        for (int j = minY; j <= maxY; j++) {
            vec.push_back('.');
        }
        map.push_back(vec);
    }
    cout << "made main empty map" << endl;

    // add the floor for part 2
    vector<char> vec1; // the empty line between the bottom and the floor
    for (int i = minY; i <= maxY; i++) {
        vec1.push_back('.');
    }
    map.push_back(vec1);

    // now do it again for the floor
    vector<char> vec2; // the empty line between the bottom and the floor
    for (int i = minY; i <= maxY; i++) {
        vec2.push_back('#');
    }
    map.push_back(vec2);

    cout << "added floor" << endl;
    cout << map.size() << ", " << map[0].size() << endl;
    

    for(string s : input) {
        vector<string> splitS = splitString(s, '-');
        for (int i = 0; i < splitS.size() - 1; i++) {
            string pair1 = splitS[i];
            string pair2 = splitS[i+1];
            pair1 = removeChar(pair1, '>');
            pair2 = removeChar(pair2, '>');
            vector<string> pair1Coords = splitString(pair1, ',');
            vector<string> pair2Coords = splitString(pair2, ',');
            int x1, y1, x2, y2;
            y1 = stoi(pair1Coords[1]);
            x1 = stoi(pair1Coords[0]) - minY;
            y2 = stoi(pair2Coords[1]);
            x2 = stoi(pair2Coords[0]) - minY;
            if (y1 == y2) {
                if (x1 < x2) {
                    for (int k = x1; k <= x2; k++) {
                        map[y1][k] = '#';
                    }
                } else {
                    for (int k = x2; k <= x1; k++) {
                        map[y1][k] = '#';
                    }
                }
            } 
            else if (x1 == x2) {
                if (y1 < y2) {
                    for (int k = y1; k <= y2; k++) {
                        map[k][x1] = '#';
                    }
                } else {
                    for (int k = y2; k <= y1; k++) {
                        map[k][x1] = '#';
                    }
                }
            }
        }
    }

    return map;

}

bool canMove(int startY, int startX, vector<vector<char> > &map) {
    if (startX >= map.size() || startY >= map[0].size()) {
        return false;
    }
    if (map[startX][startY] == 'o' && startX == 0) {
        return false;
    }
    if (map[startX][startY] == '#' && startX+1 < map.size() && map[startX+1][startY-1] != '.' && map[startX+1][startY+1] != '.') {
        map[startX-1][startY] = 'o';
        cout << "return 1" << endl;
        return true;
    } else if (map[startX][startY] == 'o') {
        if (startX+1 < map.size() && startY-1 >= 0) {
            if (map[startX+1][startY-1] == 'o') {
                if (startY+1 < map[0].size()) {
                    if (map[startX+1][startY+1] == 'o') {
                        map[startX][startY] = 'o';
                        return true;
                    }
                }
            }
        }
    } 
    else if (map[startX][startY] == '.' && startX+1 < map.size() && (map[startX+1][startY] == 'o' || map[startX+1][startY] == '#')) {
        if (map[startX+1][startY-1] == 'o' || map[startX+1][startY-1] == '#') {
            if (map[startX+1][startY+1] == 'o' || map[startX+1][startY+1] == '#') {
                // on top of other snow in all directions
                map[startX][startY] = 'o';
                return true;
            }
        }
    }

    if (startX+1 < map.size() && map[startX+1][startY] == '.') {
        // move down
        cout << "recurse 1 " << endl;
        return canMove(startY, startX+1, map);
    }
    if (startX+1 < map.size() && startY-1 >= 0 && map[startX+1][startY-1] == '.') {
        // move left and down
        cout << "recurse 2" << endl;
        return canMove(startY-1, startX+1, map);
    }
    else if (startX+1 == map.size()) {
        return false;
    }
    if (startX+1 < map.size() && startY+1 < map[0].size() && map[startX+1][startY+1] == '.') {
        // move right and down
        cout << "recurse 3" << endl;
        return canMove(startY+1, startX+1, map);
    }
    // end condition for Part 2
    if (startX-1 == 0) {
        return false;
    }

    cout << map[startX][startY] << endl;
    return false;
}

int runSimulation(vector<vector<char> > &map, int minY) {
    bool moved = true;
    int movesMade = 0;
    int startY = 500 - minY + Y_BUFFER;   // subtract values for part 2
    int startX = 0; 
    cout << startY << endl;
    cout << "Running simulation..." << endl;
    while (moved) {
        bool t = canMove(startY, startX, map);
        if (t) {
            movesMade += 1;
        } else {
            moved = false;
        }
    }
    

    return movesMade;
}

int main() {
    vector<string> values = getValuesFromFile("input.txt");
    vector<vector<char> > map = initializeMap(values);
    int minY = findMinY(values);
    int maxY = findMaxY(values);
    int movesMade = runSimulation(map, minY);
    cout << movesMade << endl;
    // for (int i = 0; i < map.size(); i++) {
    //     vector<char> v = map[i];
    //     for (int j = 0; j < v.size(); j++) {
    //         char c = v[j];
    //         cout << c;
    //     }
    //     cout << endl;
    // }
    // Part 1: 618
    // Part 2: 26358

    return 0;
}