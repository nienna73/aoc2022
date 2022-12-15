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

        void print() {
            cout << x << ", " << y << endl;
            cout << cost << endl;
            cout << c << endl;
            cout << visited << endl;
            cout << endl;
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

vector<tuple<int, int> > getAllAs(vector<vector<Point> > map) {
    vector<tuple<int, int> > ret;
    for (vector<Point> v : map) {
        for (Point p : v) {
            if (p.c == 'a') {
                tuple<int, int> t = make_tuple(p.x, p.y);
                ret.push_back(t);
            }
        }
    }
    return ret;
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

vector<vector<int> > canMove(vector<vector<Point> > map, int startX, int startY, vector<vector<int> > distance) {
    Point currentPoint = map[startX][startY];
    int cost = distance[startX][startY] + 1;
    char startChar = currentPoint.c;
    if ((startX -1 >= 0) && (startChar >= map[startX-1][startY].c - 1) == 1) {
        // move up
        if (cost < distance[startX-1][startY]) {
            distance[startX-1][startY] = cost;
        }
    }
    if ((startY -1 >= 0) && (startChar >= map[startX][startY-1].c - 1) == 1) {
        // move left
        if (cost < distance[startX][startY-1]) {
            distance[startX][startY-1] = cost;
        }
    } 
    if ((startY + 1) < map[0].size() && (startChar >= map[startX][startY+1].c - 1) == 1) {
        // move right
        if (cost < distance[startX][startY+1]) {
            distance[startX][startY+1] = cost;
        }
    }
    if ((startX+1) < map.size() && (startChar >= map[startX+1][startY].c - 1) == 1) {
        // move down
        if (cost < distance[startX+1][startY]) {
            distance[startX+1][startY] = cost;
        }
    }
    return distance;
}

vector<tuple<int, int> > minDist(vector<vector<int> > distance, vector<vector<bool> > seen, int k, int j) {
    vector<tuple<int, int> > ret;
    int minDistance = distance[k][j] + 1;
    if (k+1 < distance.size() && seen[k+1][j] == false && distance[k+1][j] <= minDistance) {
        tuple<int, int> t = make_tuple(k+1, j);
        ret.push_back(t);
    }
    if (k-1 >= 0 && seen[k-1][j] == false && distance[k-1][j] <= minDistance) {
        tuple<int, int> t = make_tuple(k-1, j);
        ret.push_back(t);
    }
    if (j+1 < distance[0].size() && seen[k][j+1] == false && distance[k][j+1] <= minDistance) {
        tuple<int, int> t = make_tuple(k, j+1);
        ret.push_back(t);
    }
    if (j-1 >= 0 && seen[k][j-1] == false && distance[k][j-1] <= minDistance) {
        tuple<int, int> t = make_tuple(k, j-1);
        ret.push_back(t);
    }
    return ret;
}

vector<vector<bool> > resetSeen(vector<vector<bool> > seen) {
    int x = seen.size();
    int y = seen[0].size();
    seen.clear();
    for (int i = 0; i < x; i++) {
        vector<bool> tmp;
        for (int j = 0; j < y; j++) {
            tmp.push_back(false);
        }
        seen.push_back(tmp);
    }
    return seen;
}

long findShortestPath(vector<vector<Point> > map, int startX, int startY, int endX, int endY, long stepsTaken) {
    vector<vector<int> > distance;
    vector<vector<bool> > seen;
    for (int i = 0; i < map.size(); i++) {
        vector<int> row1;
        vector<bool> row2;
        for (int j = 0; j < map[0].size(); j++) {
            row1.push_back(GIANT_INT);
            row2.push_back(false);
        }
        distance.push_back(row1);
        seen.push_back(row2);
    }
    distance[startX][startY] = 0;
    distance = canMove(map, startX, startY, distance);
    vector<tuple<int, int> > q;
    vector<tuple<int, int> > canMoveTo = minDist(distance, seen, startX, startY);
    for (tuple<int, int> t : canMoveTo) {
        q.push_back(t);
    }

    while (!q.empty()) {
        tuple<int, int> coords = q.front();
        q.erase(q.begin());
        seen[get<0>(coords)][get<1>(coords)] = true;
        distance = canMove(map, get<0>(coords), get<1>(coords), distance);
        canMoveTo = minDist(distance, seen, get<0>(coords), get<1>(coords));
        for (tuple<int, int> t : canMoveTo) {
            if (find(q.begin(), q.end(), t) == q.end()) {
                q.push_back(t);
            }
        }
    }

    return distance[endX][endY];
}


int main() {
    vector<string> values = getValuesFromFile("input.txt");
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

    long stepsTaken = findShortestPath(map, get<0>(starts), get<1>(starts), get<0>(ends), get<1>(ends), 0);
    cout << "Part 1: " << stepsTaken << endl;
    // Part 1: 383

    long shortestPath = GIANT_INT;
    vector<tuple<int, int> > a = getAllAs(map);
    for (tuple<int, int> t : a) {
        long pathLength = findShortestPath(map, get<0>(t), get<1>(t), get<0>(ends), get<1>(ends), 0);
        if (pathLength < shortestPath) {
            shortestPath = pathLength;
        }
    }
    cout << "Part 2: " << shortestPath << endl;

    return 0;
}