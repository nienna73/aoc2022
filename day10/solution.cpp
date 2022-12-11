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

vector<bool> part2(vector<string> values) {
    int moves = 0;
    int x = 1;
    vector<bool> canSee;
    vector<int> sprite;
    sprite.push_back(x);
    sprite.push_back(x-1);
    sprite.push_back(x+1);

    for (string &s : values) {
        vector<string> split = splitString(s, ' ');
        if (split.size() == 1) {
            moves += 1;
            canSee.push_back(find(sprite.begin(), sprite.end(), moves % 40) != sprite.end());
        } else {
            moves += 1;
            canSee.push_back(find(sprite.begin(), sprite.end(), moves % 40) != sprite.end());
            moves += 1;
            x += stoi(split[1]);
            sprite.clear();
            sprite.push_back(x);
            sprite.push_back(x-1);
            sprite.push_back(x+1);
            canSee.push_back(find(sprite.begin(), sprite.end(), moves % 40) != sprite.end());
        }
    }

    return canSee;
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

    vector<bool> crt = part2(values);
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