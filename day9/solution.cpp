#include "../getValuesFromFile.h"
#include "../split.h"
#include <vector>
#include <string>
#include <iostream>

class Head{
    public:
        signed int x, y;
};

class Tail{
    public:
        signed int x, y;
        vector<string> uniqueCoords;

        void operator=(const Tail &rhs) {
            this->x = rhs.x;
            this->y = rhs.y;
            this->uniqueCoords = rhs.uniqueCoords;
        }
};

bool isAdjacent(Tail head, Tail tail) {
    if (head.x == tail.x && head.y == tail.y) {
        return true;
    }

    if (head.x == tail.x +1 && head.y == tail.y) {
        return true;
    }

    if (head.x == tail.x - 1 && head.y == tail.y) {
        return true;
    }

    if (head.x == tail.x + 1 && head.y == tail.y + 1) {
        return true;
    }

    if (head.x == tail.x - 1 && head.y == tail.y + 1) {
        return true;
    }

    if (head.x == tail.x - 1 && head.y == tail.y - 1) {
        return true;
    }

    if (head.x == tail.x + 1 && head.y == tail.y - 1) {
        return true;
    }

    if (head.x == tail.x && head.y == tail.y + 1) {
        return true;
    }

    if (head.x == tail.x && head.y == tail.y - 1) {
        return true;
    }

    return false;
}

void updateCoords(Tail *tail) {
    string coords = "";
    coords += to_string(tail->x);
    coords += to_string(tail->y);
    if (std::find(tail->uniqueCoords.begin(), tail->uniqueCoords.end(), coords) == tail->uniqueCoords.end()) {
        tail->uniqueCoords.push_back(coords);
    }
}

Tail updateCoordsWithRet(Tail tail) {
    string coords = "";
    coords += to_string(tail.x);
    coords += to_string(tail.y);
    if (std::find(tail.uniqueCoords.begin(), tail.uniqueCoords.end(), coords) == tail.uniqueCoords.end()) {
        tail.uniqueCoords.push_back(coords);
    }
    return tail;
}

void moveTail(Tail *head, Tail *tail) {
    
    if (isAdjacent(*head, *tail)) {
        return;
    }
    if (head->x - tail->x < 0) {
        tail->x -= 1;
    } else if (head->x - tail->x > 0) {
        tail->x += 1;
    }

    if (head->y - tail->y < 0) {
        tail->y -= 1;
    } else if (head->y - tail->y > 0) {
        tail->y += 1;
    }
}

Tail moveTailWithRet(Tail head, Tail tail) {
    
    if (isAdjacent(head, tail)) {
        return tail;
    }


    if (head.x == tail.x && head.y == tail.y + 2) {
        tail.y = tail.y + 1;
        return tail;
    }

    if (head.x == tail.x && head.y == tail.y - 2) {
        tail.y = tail.y - 1;
        return tail;
    }

    if (head.x == tail.x +2 && head.y == tail.y) {
        tail.x = tail.x + 1;
        return tail;
    }

    if (head.x == tail.x - 2 && head.y == tail.y) {
        tail.x = tail.x-1;
        return tail;
    }

    if (head.x == tail.x + 1 && head.y == tail.y + 2) {
        tail.x = tail.x + 1;
        tail.y = tail.y + 1;
        return tail;
    }

    if (head.x == tail.x -1  && head.y == tail.y + 2) {
        tail.x = tail.x - 1;
        tail.y = tail.y + 1;
        return tail;
    }

    if (head.x == tail.x - 2 && head.y == tail.y - 1) {
        tail.x = tail.x - 1;
        tail.y = tail.y - 1;
        return tail;
    }

    if (head.x == tail.x + 2 && head.y == tail.y - 1) {
        tail.x = tail.x + 1;
        tail.y = tail.y - 1;
        return tail;
    }

    if (head.x == tail.x + 2 && head.y == tail.y + 1) {
        tail.x = tail.x + 1;
        tail.y = tail.y + 1;
        return tail;
    }

    if (head.x == tail.x - 2 && head.y == tail.y + 1) {
        tail.x = tail.x - 1;
        tail.y = tail.y + 1;

        return tail;
    }

    if (head.x == tail.x + 1 && head.y == tail.y - 2) {
        tail.y = tail.y - 1;
        tail.x = tail.x + 1;
        return tail;
    }

    if (head.x == tail.x - 1 && head.y == tail.y - 2) {
        tail.y = tail.y - 1;
        tail.x = tail.x - 1;
        return tail;
    }

    return tail;
}

void move(Tail *head, string direction) {
    if (direction == "L") {
        // move left, or down in x
        head->x -= 1;
    } else if (direction == "U") {
        // move up, or up in y
        head->y += 1;
    } else if (direction == "R") {
        // move right, or up in x
        head->x += 1;
    } else if (direction == "D") {
        // move down, or down in y
        head->y -= 1;
    }
}

void runSimulation(vector<string> values, vector<Tail> *tails) {
    for (string &val : values) {
        vector<string> pairs = splitString(val, ' ');
        string direction = pairs[0];
        int distance = stoi(pairs[1]);
        for (int i = 0; i < distance; i++) {
            for (int j = 0; j < tails->size() - 1; j++) {
                if (j == 0) {
                    move(&tails->at(j), direction);
                }
                moveTail(&tails->at(j), &tails->at(j+1));
                updateCoords(&tails->at(j+1));
            }
        }
    }
}

vector<string> getIntersectionOfCoords(vector<Tail> tails) {
    vector<string> ret;
    for(Tail &tail : tails) {
        for (string &s : tail.uniqueCoords) {
            if (find(ret.begin(), ret.end(), s) == ret.end()) {
                ret.push_back(s);
            }
        }
    }

    return ret;
    
}

#define IS_TRUE(x) { if (!x) { cout << __FUNCTION__ << " failed at line " << __LINE__ << endl; }};

void test_isAdjacent() {
    Tail tail;
    Tail head;

    tail.x = 0;
    tail.y = 0;
    head.x = 0;
    head.y = 0;
    IS_TRUE(isAdjacent(head, tail));

    head.x = 1;
    head.y = 1;
    IS_TRUE(isAdjacent(head, tail));

    tail.y = 1;
    IS_TRUE(isAdjacent(head, tail));

    tail.x = 2;
    tail.y = 2;
    IS_TRUE(isAdjacent(head, tail));

    tail.x = 5;
    tail.y = 4;
    IS_TRUE(!isAdjacent(head, tail));

    head.x = 1;
    head.y = 3;
    IS_TRUE(!isAdjacent(head, tail));

    tail.x = 0;
    tail.y = 0;
    head.x = -1;
    head.y = -1;
    IS_TRUE(isAdjacent(head, tail));

}

void test_moveTail() {
    Tail tail;
    Tail head;

    tail.x = 0;
    tail.y = 0;
    head.x = 0;
    head.y = 0;
    moveTail(&head, &tail);
    IS_TRUE((tail.x == 0 && tail.y == 0));

    head.x = 1;
    head.y = 1;
    moveTail(&head, &tail);
    IS_TRUE((tail.x == 0 && tail.y == 0));

    head.x = 1;
    head.y = 2;
    moveTail(&head, &tail);
    IS_TRUE((tail.x == 1 && tail.y == 1));

    head.x = 0;
    head.y = 3;
    moveTail(&head, &tail);
    IS_TRUE((tail.x == 0 && tail.y == 2));
    IS_TRUE(isAdjacent(head, tail));

    tail.x = 0;
    tail.y = 0;
    head.x = -1;
    head.y = -2;
    moveTail(&head, &tail);
    IS_TRUE(isAdjacent(head, tail));

    head.x = 1;
    head.y = 3;
    IS_TRUE(!isAdjacent(head, tail));

}

void test_updateCoords() {
    vector<string> coords;
    coords.push_back("00");
    Tail tail;
    tail.x = 0;
    tail.y = 0;
    tail.uniqueCoords = coords;
    updateCoords(&tail);
    IS_TRUE((tail.uniqueCoords == coords));

    tail.x = 3;
    updateCoords(&tail);
    coords.push_back("30");
    IS_TRUE((tail.uniqueCoords == coords));

    tail.y = 3;
    updateCoords(&tail);
    coords.push_back("33");
    IS_TRUE((tail.uniqueCoords == coords));

    tail.x = 0;
    tail.y = 0;
    updateCoords(&tail);
    IS_TRUE((tail.uniqueCoords == coords));
}

int main() {
    test_isAdjacent();
    test_moveTail();
    test_updateCoords();

    vector<string> values = getValuesFromFile("input.txt");
    Tail head;
    head.x = 0;
    head.y = 0;

    Tail tail;
    tail.x = 0;
    tail.y = 0;
    vector<string> coords;
    coords.push_back("00");
    tail.uniqueCoords = coords;
    vector<Tail> tails;
    for (int i = 1; i < 10; i++) {
        Tail t;
        t.x = 0;
        t.y = 0;
        t.uniqueCoords = coords;
        tails.push_back(t);
    }
    tails.push_back(head);

    runSimulation(values, &tails);
    vector<string> allCoords = getIntersectionOfCoords(tails);
    cout << allCoords.size() << endl;
    cout << tails.end()->uniqueCoords.size() << endl;
    // 5999 is too low
    // 6089 is too low
    // 6232 is wrong
}