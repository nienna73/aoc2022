#include "../getValuesFromFile.h"
#include <vector>
#include <string>
#include <iostream>


vector<vector<string> > initializeRocks() {
    vector<vector<string> > ret;
    // first rock: ####
    string s = "####";
    vector<string> vec;
    vec.push_back(s);
    ret.push_back(vec);

    // second rock:
    //   .#.
    //   ###
    //   .#.
    string s1 = ".#.";
    string s2 = "###";
    vector<string> vec2;
    vec2.push_back(s1);
    vec2.push_back(s2);
    vec2.push_back(s1);
    ret.push_back(vec2);

    // third rock:
    //  ..#
    //  ..#
    //  ###
    string t1 = "..#";
    string t2 = "###";
    vector<string> vec3;
    vec3.push_back(t1);
    vec3.push_back(t1);
    vec3.push_back(t2);
    ret.push_back(vec3);

    // fourth rock:
    // #
    // #
    // #
    // #
    string u = "#";
    vector<string> vec4;
    vec4.push_back(u);
    vec4.push_back(u);
    vec4.push_back(u);
    vec4.push_back(u);
    ret.push_back(vec4);

    // fifth rock:
    // ##
    // ##
    string v = "##";
    vector<string> vec5;
    vec5.push_back(v);
    vec5.push_back(v);
    ret.push_back(vec5);

    return ret;
}

int getWidthOfRock(vector<string> rock) {
    int width = 0;
    for (string s : rock) {
        if (s.length() > width) {
            width = s.length();
        }
    }
    return width;
}

void updateWind(int &left, char c, vector<vector<char> > map, int width, int bottom) {
    if (c == '>') {
        left++;
    } else {
        left--;
    }
    if (left < 0) {
        left = 0;
    }
    if (left + width > 7) {
        left = 6 - width;
    }
    while (map[bottom][left] == '#') {
        left++;
    }
}

bool canFitRock(vector<vector<char> > map, int bottom, vector<string> rock, int left) {
    // can fit rock in row with left edge of rock at position left
    vector<char> row = map[bottom];
    string bottomOfRock = rock[rock.size() - 1];
    if (bottomOfRock == ".#.") {
        bottomOfRock = "###";
    }
    int rockWidth = bottomOfRock.length();
    for (int i = 0; i < rockWidth; i++) {
        if (left + i < row.size()) {
            if (row[left+i] != '.') {
                return false;
            }
        }
    }
    if (bottomOfRock == "###") {
        if (map[bottom+1][left+1] != '.') {
            return false;
        }
    }
    return true;
}

void placeRockInMap(vector<vector<char> > &map, vector<string> rock, int left, int bottom) {
    int top = bottom - rock.size() + 1;
    int tmpLeft = left;
    for (string s : rock) {
        for (char c : s) {
            if (c == '.') {
                tmpLeft++;
                continue;
            }
            map[top][tmpLeft] = c;
            tmpLeft++;
        }
        tmpLeft = left;
        top++;
    }

    // for (int i = bottom - rock.size(); i < map.size(); i++) {
    //     vector<char> v = map[i];
    //     for (char c : v) {
    //         cout << c;
    //     }
    //     cout << endl;
    // }
}

void moveRock(vector<string> &rock, string wind, int &windIndex, vector<vector<char> > &map, int bottom, int left) {
    // need current coordinates
    // move in direction of wind
    // try to move down
    // if at 0, stop move
    // if wind into wall, no wind
    char windDirection = wind[windIndex%wind.length()];
    windIndex++;
    int width = getWidthOfRock(rock);

    updateWind(left, windDirection, map, width, bottom);

    
    if (bottom + 1 < map.size()) {
        string bottomOfRock = rock[rock.size() - 1];
        if (bottomOfRock == ".#.") {
            if (canFitRock(map, bottom, rock, left)) {
                moveRock(rock, wind, windIndex, map, bottom+1, left);
            } else {
                placeRockInMap(map, rock, left, bottom);
            }
        }
        else if (canFitRock(map, bottom+1, rock, left)) {
            moveRock(rock, wind, windIndex, map, bottom+1, left);
        } 
        else {
            placeRockInMap(map, rock, left, bottom);
        }
    } else {
        placeRockInMap(map, rock, left, bottom);
    }
}

int getHeight(vector<vector<char> > map) {
    int first = -1;
    for (int i = 0; i < map.size(); i++) {
        if (find(map[i].begin(), map[i].end(), '#') != map[i].end()) {
            first = i;
            break;
        }
    }
    return map.size() - first;
}

void runSimulation(string wind, vector<vector<string> > rocks) {
    vector<vector<char> > map(2022*4, vector<char> (7, '.'));
    int windIndex = 0;
    int bottom = map.size() - 4;
    for (int i = 0; i < 2022; i++) {
        if (i % 50 == 0) {
            cout << "Finished round " << i << endl;
        }
        vector<string> rock = rocks[i%5];
        int left = 2;
        if (rock[rock.size() -1] == ".#.") {
            left = 3;
        }
        moveRock(rock, wind, windIndex, map, bottom, left);
        bottom = bottom - rock.size();
    }

    cout << getHeight(map) << endl;

}


int main() {
    vector<string> wind = getValuesFromFile("test-input.txt");
    vector<vector<string> > rocks = initializeRocks();
    runSimulation(wind[0], rocks);

}