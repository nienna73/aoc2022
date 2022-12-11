#include "../getValuesFromFile.h"
#include "../split.h"
#include <vector>
#include <string>
#include <iostream>
#include <map>


map<int, long> cycle(vector<string> input) {
    long x = 1;
    signed toAdd = 0;
    map<int, long> values;
    int numCycles = 0;
    vector<int> sprite;
    for (int i = 0; i < input.size(); i++) {
        vector<string> split = splitString(input[i], ' ');
        x += toAdd;
        if (split.size() == 1) {
            toAdd = 0;
            numCycles += 1;
            values[numCycles] = x;
        } else if (split.size() == 2) {
            toAdd = stol(split[1]);
            numCycles += 1;
            values[numCycles] = x;
            numCycles += 1;
            values[numCycles] = x + toAdd;
        }
    }

    return values;
}

void drawSprite(vector<int> sprite) {
    for (int i = 0; i < 40; i++) {
        if (find(sprite.begin(), sprite.end(), i) != sprite.end()) {
            cout << "#";
        } else {
            cout << ".";
        }
    }
    cout << endl;
}

map<int, bool> part2(vector<string> input) {
    long x = 1;
    signed toAdd = 0;
    map<int, bool> values;
    int numCycles = 0;
    vector<int> sprite;
    for (int i = 0; i < input.size(); i++) {
        vector<string> split = splitString(input[i], ' ');
        x += toAdd;
        sprite.clear();
        sprite.push_back(x-1);
        sprite.push_back(x);
        sprite.push_back(x+1);
        if (split.size() == 1) {
            toAdd = 0;
            numCycles += 1;
            if (find(sprite.begin(), sprite.end(), (numCycles % 40)) != sprite.end()) {
                values[numCycles] = true;
            } else {
                values[numCycles] = false;
            }
        } else if (split.size() == 2) {
            toAdd = stol(split[1]);
            numCycles += 1;
            if (find(sprite.begin(), sprite.end(), (numCycles% 40)) != sprite.end()) {
                values[numCycles] = true;
            } else {
                values[numCycles] = false;
            }
            numCycles += 1;
            if (find(sprite.begin(), sprite.end(), (numCycles % 40)) != sprite.end()) {
                values[numCycles] = true;
            } else {
                values[numCycles] = false;
            }
            sprite.clear();
            sprite.push_back(x-1);
            sprite.push_back(x);
            sprite.push_back(x+1);
        }
    }

    return values;
}

int main() {
    vector<string> values = getValuesFromFile("input.txt");

    map<int, long> out = cycle(values);

    signed long sum = 0;
    sum += out[19] * 20;
    sum += out[59] * 60;
    sum += out[99] * 100;
    sum += out[139] * 140;
    sum += out[179] * 180;
    sum += out[219] * 220;
    cout << "Part 1: " << sum << endl;

    map<int, bool> crt = part2(values);
    cout << crt.size() << endl;
    for (int i = 0; i < 240; i++) {
        if (i % 40 == 0) {
            cout << endl;
        }
        if (crt[i]) {
            cout << "#";
        } else {
            cout << ".";
        }
    }
    cout << endl;
    return 0;
}