#include "../getValuesFromFile.h"
#include "../split.h"
#include <vector>
#include <string>
#include <iostream>
#include <cmath>

class Valve {
    public:
        int flowRate;
        vector<Valve*> tunnels;
        vector<string> placeholderTunnels;
        string name;
        bool isOpen;
        int openedOn;
        vector<tuple<Valve*, int> > distancesTo;

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
            distancesTo = rhs->distancesTo;
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
        for (string w : splitTunnels) {
            vector<string> anotherSplit = splitString(w, ' ');
            for (string q : anotherSplit) {
                if (q.length() == 2 && q != "to") {
                    placeholders.push_back(q);
                }
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

int findDistanceBetween(Valve &v, Valve &u) {
    int ret = 0;
    if (find(v.tunnels.begin(), v.tunnels.end(), &u) != v.tunnels.end()) {
        return ret + 1;
    } else {
        vector<Valve> toTry;
        vector<Valve> tried;
        Valve current = v;
        ret++;
        tried.push_back(v);
        for (Valve *w : v.tunnels) {
            toTry.push_back(*w);
        }
        while (!toTry.empty()) {
            Valve w = toTry[0];
            toTry.erase(toTry.begin());
            tried.push_back(w);
            if (find(w.tunnels.begin(), w.tunnels.end(), &u) != w.tunnels.end()) {
                return ret +1;
            } 
            else {
                for (Valve *q : w.tunnels) {
                    if (find(tried.begin(), tried.end(), *q) == tried.end()) {
                        toTry.push_back(*q);
                    }
                }
            }
            if (find(current.tunnels.begin(), current.tunnels.end(), &w) == current.tunnels.end()) {
                ret += 1;
                current = w;
            }
        }
    }
    return -1;
}

void initializeDistancesTo(vector<Valve> &valves) {
    for (Valve &v : valves) {
        for (Valve &u : valves) {
            vector<Valve> tried;
            if (v == u) {
                continue;
            }
            tried.push_back(v);
            int distanceTo = findDistanceBetween(v, u);
            tuple<Valve*, int> add = make_tuple(&u, distanceTo);
            v.distancesTo.push_back(add);
        }
    }
}

void runSimulation(vector<Valve> valves) {
    int i = 30;
    Valve* current = getRealTunnel(valves, "AA");
    vector<string> opened;
    int totalAirFlow = 0;
    Valve* best;
    int ret = 0;
    while (i > 0) {
        int timeDelay = 0;
        int airFlow = 0;
        int airFlowToAdd = 0;
        int best = -30;
        int time = 0;
        int measure = -30;
        Valve *b;
        cout << current->name << endl;
        sort(current->distancesTo.begin(), current->distancesTo.end(), [](const tuple<Valve*, int>& lhs, const tuple<Valve*, int>& rhs) {
            return get<1>(lhs) > get<1>(rhs);
        });
        for (tuple<Valve*, int> t : current->distancesTo) {
            Valve *v = get<0>(t);
            time = get<1>(t);
            if (time < 0) {
                continue;
            }
            if (find(opened.begin(), opened.end(), v->name) != opened.end()) {
                continue;
            }
            if (v->flowRate == 0) {
                continue;
            }
            airFlow = v->flowRate* (i - time);
            measure = v->flowRate / time;
            // cout << v->name << ": " << measure << endl;
            if (measure > best) {
                best = measure;
                b = v;
                timeDelay = time;
                airFlowToAdd = airFlow;
            } if (measure == best) {
                if (time < timeDelay) {
                    best = measure;
                    b = v;
                    timeDelay = time;
                    airFlowToAdd = airFlow;
                }
            }
        }
        if (timeDelay != 0) {
            i -= timeDelay;
        } else {
            i--;
        }
        cout << "time left " << i << endl;
        ret += airFlowToAdd;
        opened.push_back(b->name);
        current = b;
    }

    cout << "Total airflow: " << ret << endl;
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
    initializeDistancesTo(valves);

    runSimulation(valves);
    Valve* v = getRealTunnel(valves, "CC");
    // for (tuple<Valve*, int> t : v->distancesTo) {
    //     cout << get<0>(t)->name << ": " << get<1>(t) << endl;
    // }
    // d -> b -> j -> h -> e -> c
    // Part 1: 1038 is too low
}