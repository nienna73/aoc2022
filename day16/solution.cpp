#include "../getValuesFromFile.h"
#include "../split.h"
#include <vector>
#include <string>
#include <iostream>

class Valve {
    public:
        int flowRate;
        vector<Valve*> tunnels;
        vector<string> placeholderTunnels;
        string name;
        bool isOpen;
        int openedOn;

        bool operator==(Valve rhs) {
            if (name == rhs.name) {
                return true;
            } else {
                return false;
            }
        }

        bool operator!=(Valve rhs) {
            if (name == rhs.name) {
                return false;
            } else {
                return true;
            }
        }

        void operator=(Valve *rhs) {
            name = rhs->name;
            flowRate = rhs->flowRate;
            tunnels = rhs->tunnels;
            placeholderTunnels = rhs->placeholderTunnels;
            isOpen = rhs->isOpen;
            openedOn = rhs->openedOn;
        }
};

vector<Valve> initializeValves(vector<string> input) {
    vector<Valve> ret;
    int i = 0;
    for (string s : input) {
        vector<string> split = splitString(s, ';');
        vector<string> splitValve = splitString(split[0], ' ');
        Valve v;
        v.name = splitValve[1];
        v.isOpen = false;
        v.openedOn = 0;
        vector<string> rate = splitString(splitValve[4], '=');
        int flowRate = stoi(rate[1]);
        v.flowRate = flowRate;
        vector<string> splitTunnels = splitString(split[1], ',');
        vector<string> placeholders;
        if (splitTunnels.size() == 2) {
            string firstTunnel = "";
            firstTunnel += splitTunnels[1][1];
            firstTunnel += splitTunnels[1][2];
            placeholders.push_back(firstTunnel);
        }
        vector<string> moreTunnels = splitString(splitTunnels[0], ' ');
        for (string w : moreTunnels) {
            if (w.length() == 2 && w != "to") {
                placeholders.push_back(w);
            }
        }
        v.placeholderTunnels = placeholders;
        ret.push_back(v);
        i++;
    }
    return ret;
}

Valve* getRealTunnel(vector<Valve> &valves, string name) {
    for (Valve &v : valves) {
        if (v.name == name) {
            return &v;
        }
    }
}

void initializeTunnels(vector<Valve> &valves) {
    for (Valve &v : valves) {
        for (string s : v.placeholderTunnels) {
            Valve* u = getRealTunnel(valves, s);
            v.tunnels.push_back(u);
        }
    }

}

tuple<int, Valve> pathToBestValue(Valve active, vector<string> opened) {
    cout << "Current name: " << active.name << endl;
    int ret = 0;
    int curFlowRate = active.flowRate;
    Valve best = active;
    for (Valve *v : active.tunnels) {
        if (v->flowRate > curFlowRate) {
            if (find(opened.begin(), opened.end(), v->name) == opened.end()) {
                cout << "Setting best to " << v->name << endl;
                best = v;
            }
        }
    }
    if (best == active) {
        // find the highest neighbour instead
        cout << "need to get highest neighbour" << endl << endl;
        ret = 1;
        Valve *secondBest = &active;
        int secondBestFlow = 0;
        cout << "active tunnels: " << active.tunnels.size() << endl;
        for (Valve *v : active.tunnels) {
            if (find(opened.begin(), opened.end(), v->name) == opened.end()) {
                if (v->flowRate > secondBestFlow) {
                    cout << "setting best to " << v->name << endl;
                    secondBest = v;
                    secondBestFlow = v->flowRate;
                }
            }
        }
        cout << "Changing to: " << secondBest->name << endl;
        if (*secondBest != active) {
            return make_tuple(ret, *secondBest);
        } else {
            ret = 1;
            *secondBest = &active;
            secondBestFlow = 0;
            cout << "active tunnels: " << active.tunnels.size() << endl;
            for (Valve *v : active.tunnels) {
                if (v->flowRate > secondBestFlow) {
                    cout << "setting best to " << v->name << endl;
                    secondBest = v;
                    secondBestFlow = v->flowRate;
                }
            }
            cout << "Changing to: " << secondBest->name << endl;
            return make_tuple(ret, *secondBest);
        }
    } else {
        cout << "Changing to: " << best.name << endl;
        return make_tuple(ret, best);
    }
}

void runSimulation(vector<Valve> valves) {
    int i = 30;
    Valve* current = getRealTunnel(valves, "AA");
    vector<string> opened;
    int totalAirFlow = 0;
    while (i > 0) {
        tuple<int, Valve> turn = pathToBestValue(*current, opened);
        cout << "after the call " << endl;
        int cost = get<0>(turn);
        Valve n = get<1>(turn);
        current = &n;
        i -= cost;
        current = getRealTunnel(valves, n.name);
        Valve c = *current;
        c.isOpen = true;
        opened.push_back(c.name);
        i--;
        c.openedOn = i;
        totalAirFlow += c.flowRate * i;
        cout << "Time left: " << i << endl;
    }
    cout << "Total airflow: " << totalAirFlow << endl;
}

void getTotalAirFlow(vector<Valve> valves) {
    int total = 0;
    for (Valve &v : valves) {
        cout << v.isOpen << endl;
        if (v.isOpen) {
            total += v.flowRate * v.openedOn;
        }
    }
    cout << total << endl;
}

int main() {
    vector<string> values = getValuesFromFile("test-input.txt");
    vector<Valve> valves = initializeValves(values);
    initializeTunnels(valves);
    for (Valve v : valves) {
        cout << v.tunnels.size() << endl;
    }
    runSimulation(valves);
    getTotalAirFlow(valves);
}