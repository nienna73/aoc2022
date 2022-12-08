#include "../getValuesFromFile.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class SeaCucumber {
    public:
        int x, y;
        string direction;
        int next_x, next_y;
        bool cukeCanMove;
};

vector<SeaCucumber> initializeSeaCucumbers(vector<string> values) {
    int height = values.size();     // y-axis
    int width = values[0].length(); // x-axis

    vector<SeaCucumber> seaCucumbers;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            char c = values[i][j];
            if (c != '.') {
                SeaCucumber sc;
                sc.x = i;
                sc.y = j;
                sc.next_x = -1;
                sc.next_y = -1;
                sc.cukeCanMove = false;

                if (c == 'v') {
                    sc.direction = "south";
                } else if (c == '>') {
                    sc.direction = "east";
                } else {
                    cout << "Not a sea cucumber?" << endl;
                    vector<SeaCucumber> incorrectInput;
                    return incorrectInput;
                }
                seaCucumbers.push_back(sc);
            }

        }
    }

    return seaCucumbers;
}

void canMove(vector<vector<bool> > mapOfCukes, SeaCucumber &activeCuke, int height, int width) {
    int pos_x = activeCuke.x;
    int pos_y = activeCuke.y;
    int next_pos_x;
    int next_pos_y;
    bool cukeCanMove = true;
    if (activeCuke.direction == "south") {
        // move down, or up in y
        next_pos_x = pos_x;
        next_pos_y = pos_y + 1;
        if (next_pos_y >= height) {
            next_pos_y = 0;
        }
    } else if (activeCuke.direction == "east") {
        // move right, or up in x
        next_pos_x = pos_x + 1;
        if (next_pos_x >= width) {
            next_pos_x = 0;
        }
        next_pos_y = pos_y;
    }

    if (mapOfCukes[next_pos_x][next_pos_y]) {
        cukeCanMove = false;
        next_pos_x = -1;
        next_pos_y = -1;
    }

    activeCuke.cukeCanMove = cukeCanMove;
    activeCuke.next_x = next_pos_x;
    activeCuke.next_y = next_pos_y;

    return;
}

bool move(vector<SeaCucumber> &seaCucumbers, string direction) {
    bool didMove = false;
    int length = seaCucumbers.size();
    for (int i = 0; i < length; i++) {
        SeaCucumber cuke = seaCucumbers[i];
        if (cuke.direction == direction) {
            if (cuke.cukeCanMove) {
                if (cuke.next_x != -1 && cuke.next_y != -1) {
                    cuke.x = cuke.next_x;
                    cuke.y = cuke.next_y;
                    cuke.next_x = -1;
                    cuke.next_y = -1;
                    seaCucumbers[i] = cuke;
                    didMove = true;
                }
            }
        }
    }
    return didMove;
}

vector<vector<bool> > initializeMap(vector<SeaCucumber> seaCucumbers, int height, int width) {
    vector<vector<bool> > map;

    vector<bool> temp(width, false);
    for (int i = 0; i < height; i++) {
        map.push_back(temp);
    }

    for (SeaCucumber &cuke : seaCucumbers) {
        map[cuke.x][cuke.y] = true;
    }

    return map;
}

void printBoard(vector<vector<bool> > map) {
    for (vector<bool> &row : map) {
        int l = row.size();
        for (int i = 0; i < l; i++) {
            bool val = row[i];
            cout << val;
        }
        cout << endl;
    }
}

int runSimulation(vector<vector<bool> > map, vector<SeaCucumber> seaCucumbers, int height, int width) {
    bool didMoveEast = true;
    bool didMoveSouth = true;
    long int moves = 0;
    while (didMoveEast || didMoveSouth) {   // one loop per round
        moves += 1;
        int length = seaCucumbers.size();
        for (SeaCucumber &cuke: seaCucumbers) {
            canMove(map, cuke, height, width);
        }
        didMoveEast = move(seaCucumbers, "east");
        didMoveSouth = move(seaCucumbers, "south");
        map = initializeMap(seaCucumbers, height, width);
        if (moves % 50 == 0) {
            printBoard(map);
            cout << "Made " << moves << " moves" << endl;
        }
        if (moves > 1000) {
            break;
        }
    }

    return moves;
}

#define IS_TRUE(x) { if (!x) cout << __FUNCTION__ << " failed at line " << __LINE__ << endl; }

void test_runSimulation() {
    vector<string> values = getValuesFromFile("2021-25-test-input.txt");
    int height = values.size();     // y-axis
    int width = values[0].length(); // x-axis

    vector<SeaCucumber> seaCucumbers = initializeSeaCucumbers(values);
    vector<vector<bool> > map = initializeMap(seaCucumbers, height, width);
    if (seaCucumbers.size() == 0) {
        return;
    }

    cout << "Running simulation..." << endl;

    int moves = runSimulation(map, seaCucumbers, height, width);
    cout << moves << endl;
    IS_TRUE((moves == 58));
}


int main() {
    test_runSimulation();
    // I'm working in quadrant 4: positive x, negative y
    // vector<string> values = getValuesFromFile("2021-25-input.txt");

    // int height = values.size();     // y-axis
    // int width = values[0].length(); // x-axis

    // vector<SeaCucumber> seaCucumbers = initializeSeaCucumbers(values);
    // if (seaCucumbers.size() == 0) {
    //     return -1;
    // }

    // int moves = runSimulation(seaCucumbers, height, width);

    return 0;
}