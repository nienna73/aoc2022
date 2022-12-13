#include "../getValuesFromFile.h"
#include <iostream>
#include <vector>
#include <string>
#include <tuple>

class Point{
    public:
        int x, y;
        int cost;
        int prevX, prevY;
        char c;
        bool visited;
        Point *prevPoint;
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
            p.cost = 0;
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
            row.push_back(make_tuple(__INT_MAX__, -1, -1));
        }
        ret.push_back(row);
    }
    return ret;
}

vector<Point> canMove(char startChar, vector<vector<Point> > map, int startX, int startY, Point currentPoint) {
    vector<Point> ret;
    cout << startX << ", " << startY << endl;
    int cost = map[startX][startY].cost + 1;
    if ((startX -1 >= 0) && (startChar <= map[startX-1][startY].c) == 1) {
        // move up
        Point p;
        p.x = startX - 1;
        p.y = startY;
        p.cost = cost;
        p.prevPoint = &currentPoint;
        ret.push_back(p);
    }
    if ((startY -1 >= 0) && (startChar <= map[startX][startY-1].c) == 1) {
        // move left
         Point p;
        p.x = startX;
        p.y = startY-1;
        p.cost = cost;
        p.prevPoint = &currentPoint;
        ret.push_back(p);
    } 
    if ((startY + 1) < map[0].size() && (startChar <= map[startX][startY+1].c) == 1) {
        // move right
         Point p;
        p.x = startX;
        p.y = startY + 1;
        p.cost = cost;
        p.prevPoint = &currentPoint;
        ret.push_back(p);
    }
    if ((startX+1) < map.size() && (startChar <= map[startX+1][startY].c) == 1) {
        // move down
         Point p;
        p.x = startX + 1;
        p.y = startY;
        p.cost = cost;
        p.prevPoint = &currentPoint;
        ret.push_back(p);
    }
    return ret;
}

long findShortestPath(vector<vector<Point> > map, vector<vector<bool> > visited, int startX, int startY, int endX, int endY, long stepsTaken) {
    long moveUp, moveLeft, moveRight, moveDown = 0;
    char startChar = map[startX][startY].c;
    if (startChar == 'S') {
            startChar = 'a';
        }
    if (startChar == 'E') {
            startChar = 'z';
        }
    Point startPoint = map[startX][startY];
    startPoint.cost = 0;
    vector<Point > q = canMove(startChar, map, startX, startY, startPoint);
    while (q.size() > 0) {
        stepsTaken++;
        Point p = q[0];
        q.erase(q.begin());
        int x = p.x;
        int y = p.y;
        if (p.visited) {
            continue;
        }
        p.visited = true;
        int currentCost = p.cost;
        if (currentCost <  p.prevPoint->cost + 1) {
            cout << "better cost found" << endl;
            // better path already found
            continue;
        } 
        else {
            p.cost =  p.prevPoint->cost + 1;
        }
        char c = p.c;
        vector<Point > tmp = canMove(c, map, x, y, p);
        for (Point n : tmp) {
            q.push_back(n);
        }
        cout << "qsize: " << q.size() << endl;
    }

    return 0;
}


int main() {
    vector<string> values = getValuesFromFile("test-input.txt");
    vector<vector<Point> > map = initializeMap(values);
    tuple<int, int> starts = getPos(map, 'S');
    tuple<int, int> ends = getPos(map, 'E');
    vector<vector<bool> > visited = initializeVisited(map);
    long stepsTaken = findShortestPath(map, visited, get<0>(starts), get<1>(starts), get<0>(ends), get<1>(ends), 0);
    cout << stepsTaken << endl;
    // Part 1:
    // 32766 is too high
    return 0;
}