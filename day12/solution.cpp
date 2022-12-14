#include "../getValuesFromFile.h"
#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <queue>


#define GIANT_INT 100000

class Point{
    public:
        int x, y;
        int cost;
        int prevX, prevY;
        char c;
        bool visited;
        Point *prevPoint;

        bool operator!=(Point* rhs) {
            if (rhs->x == x && rhs->y == y && rhs->cost == cost) {
                return false;
            }
            return true;
        }

        bool operator==(Point* rhs) {
            if (rhs->x == x && rhs->y == y && rhs->cost == cost) {
                return true;
            }
            return false;
        }
};

vector<vector<Point> > initializeMap(vector<string> input) {
    vector<vector<Point> > ret;
    for (int i = 0; i < input.size(); i++) {
        string s = input[i];
        vector<Point> row;
        for (int j = 0; j < s.length(); j++) {
            Point p;
            p.x = i;
            p.y = j;
            p.cost = GIANT_INT;
            p.c = input[i][j];
            p.visited = false;
            row.push_back(p);
        }
        ret.push_back(row);
    }
    return ret;
}

tuple<int, int> getPos(vector<vector<Point> > map, char c) {
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if (map[i][j].c == c) {
                return make_tuple(i, j);
            }
        }
    }
}

vector<vector<bool> > initializeVisited(vector<vector<Point> > map) {
    vector<vector<bool> > ret;
    for (int i = 0; i < map.size(); i++) {
        vector<bool> row;
        for (int j = 0; j < map[0].size(); j++) {
            row.push_back(false);
        }
        ret.push_back(row);
    }
    return ret;
}

vector<vector<tuple<int, int, int> > > initializeCost(vector<vector<char> > map) {
    vector<vector<tuple<int, int, int> > > ret;
    for (int i = 0; i < map.size(); i++) {
        vector<tuple<int, int, int> > row;
        for (int j = 0; j < map[0].size(); j++) {
            row.push_back(make_tuple(GIANT_INT, -1, -1));
        }
        ret.push_back(row);
    }
    return ret;
}

queue<Point> canMove(char startChar, vector<vector<Point> > map, int startX, int startY, Point* currentPoint) {
    queue<Point> ret;
    int cost = map[startX][startY].cost + 1;
    if ((startX -1 >= 0) && (startChar >= map[startX-1][startY].c) == 1) {
        // move up
        Point p;
        p.x = startX - 1;
        p.y = startY;
        p.cost = cost;
        p.prevPoint = currentPoint;
        p.visited = false;
        if (p != currentPoint->prevPoint) {
            ret.push(p);
        }
    }
    if ((startY -1 >= 0) && (startChar >= map[startX][startY-1].c) == 1) {
        // move left
         Point p;
        p.x = startX;
        p.y = startY-1;
        p.cost = cost;
        p.prevPoint = currentPoint;
        p.visited = false;
        if (p != currentPoint->prevPoint) {
            ret.push(p);
        }
    } 
    if ((startY + 1) < map[0].size() && (startChar >= map[startX][startY+1].c) == 1) {
        // move right
         Point p;
        p.x = startX;
        p.y = startY + 1;
        p.cost = cost;
        p.prevPoint = currentPoint;
        p.visited = false;
        if (p != currentPoint->prevPoint) {
            ret.push(p);
        }
    }
    if ((startX+1) < map.size() && (startChar >= map[startX+1][startY].c) == 1) {
        // move down
         Point p;
        p.x = startX + 1;
        p.y = startY;
        p.cost = cost;
        p.prevPoint = currentPoint;
        p.visited = false;
        if (p != currentPoint->prevPoint) {
            ret.push(p);
        }
    }
    return ret;
}

long findShortestPath(vector<vector<Point> > map, int startX, int startY, int endX, int endY, long stepsTaken) {
    long moveUp, moveLeft, moveRight, moveDown = 0;
    char startChar = map[startX][startY].c;
    Point startPoint = map[startX][startY];
    startPoint.cost = 0;
    startPoint.visited = true;
    queue<Point > q = canMove(startChar, map, startX, startY, &startPoint);
    vector<Point> uniqueVisited;
    uniqueVisited.push_back(startPoint);
    while (!q.empty()) {
        Point *p = &q.front();
        q.pop();
        if (p->x == endX && p->y == endY) {
            return p->cost + 1;
        }
        if (!p->visited) {
            p->visited = true;

            if (p->cost > p->prevPoint->cost + 1) {
                p->cost = p->prevPoint->cost + 1;
            }

            char startChar = p->c;
            cout << "here: " << p->c << endl;
            queue<Point> neighbours = canMove(startChar, map, startX, startY, p);
            while (!neighbours.empty()) {
                q.push(neighbours.front());
                neighbours.pop();
            }

            if (find(uniqueVisited.begin(), uniqueVisited.end(), p) == uniqueVisited.end()) {
                uniqueVisited.push_back(*p);
            }
        }
        cout << "qsize: " << q.size() << endl;
        cout << "unique visited: " << uniqueVisited.size() << endl;
        for (Point p : uniqueVisited) {
            cout << p.x << ", " << p.y << endl;
        }
    }

    return map[endX][endY].cost;
}


int main() {
    cout << (('c' >= 'a' - 1) == 1) << endl;
    vector<string> values = getValuesFromFile("test-input.txt");
    vector<vector<Point> > map = initializeMap(values);

    tuple<int, int> starts = getPos(map, 'S');
    tuple<int, int> ends = getPos(map, 'E');
    int startX = get<0>(starts);
    int startY = get<1>(starts);
    map[startX][startY].cost = 0;
    map[startX][startY].c = 'a';

    int endX = get<0>(ends);
    int endY = get<1>(ends);
    map[endX][endY].c = 'z';

    for (vector<Point> v : map) {
        for (Point p : v) {
            cout << p.c;
        }
        cout << endl;
    }

    long stepsTaken = findShortestPath(map, get<0>(starts), get<1>(starts), get<0>(ends), get<1>(ends), 0);
    // cout << stepsTaken << endl;
    // Part 1:
    // 32766 is too high
    return 0;
}