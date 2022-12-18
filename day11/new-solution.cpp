#include "../getValuesFromFile.h"
#include "../split.h"
#include <vector>
#include <string>
#include <iostream>


class Monkey {
    public:
        vector<int> items;
        char operation;
        int factor;
        int test;
        int ifTrue;
        int ifFalse;
        long itemsProcessed;

        void operator=(Monkey *rhs) {
            items = rhs->items;
            operation = rhs->operation;
            factor = rhs->factor;
            test = rhs->test;
            ifTrue = rhs->ifTrue;
            ifFalse = rhs->ifFalse;
            itemsProcessed = rhs->itemsProcessed;
        }
};

int getLast(string s) {
    vector<string> splitLine = splitString(s, ' ');
    return stoi(splitLine[splitLine.size() - 1]);
}

vector<Monkey> initializeMonkeys(vector<string> values) {
    vector<Monkey> monkeys;
    Monkey m;
    unsigned long doesNotExist = string::npos;
    for (string s : values) {
        if (s.find("Monkey") != doesNotExist) {
            m = new Monkey();
            m.itemsProcessed = 0;
        }
        if (s.find("items") != doesNotExist) {
            vector<string> stringSplit = splitString(s, ':');
            vector<string> items = splitString(stringSplit[1], ',');
            for (string i : items) {
                m.items.push_back(stoi(i));
            }
        }
        if (s.find("operation") != doesNotExist) {
            if (s.find("+") != doesNotExist) {
                m.operation = 'a';
            } else {
                m.operation = 'm';
            }
            vector<string> splitLine = splitString(s, ' ');
            if (splitLine[splitLine.size() - 1] == "old") {
                m.factor = -1;
            } else {
                m.factor = stoi(splitLine[splitLine.size() - 1]);
            }
        }
        if (s.find("Test:") != doesNotExist) {
            m.test = getLast(s);
        }
        if (s.find("true") != doesNotExist) {
            m.ifTrue = getLast(s);
        }
        if (s.find("false") != doesNotExist) {
            m.ifFalse = getLast(s);
        }
        if (s.length() == 0) {
            monkeys.push_back(m);
        }
    }
    monkeys.push_back(m);
    return monkeys;
}

vector<int> runSimulation(vector<Monkey> *monkeys, int rounds) {
    vector<int> itemsProcessed;
    for (int i = 0; i < monkeys->size(); i++) {
        itemsProcessed.push_back(0);
    }
    for (int j = 0; j < rounds; j++) {
        for (Monkey m : *monkeys) {
            // Monkey m = monkeys[i];
            int itemsProcessedByMonkey = 0;
            m.itemsProcessed += 1;
            for (int item : m.items) {
                itemsProcessedByMonkey += 1;
                int factor = m.factor;
                if (factor == -1) {
                    factor = item;
                }
                int newItem = 0;
                if (m.operation == '+') {
                    newItem = item + factor;
                } else {
                    newItem = item * factor;
                }
                
                if ((newItem % m.test) == 0) {
                    monkeys->at(m.ifTrue).items.push_back(newItem);
                } else {
                    monkeys->at(m.ifFalse).items.push_back(newItem);
                }
            }
            m.items.clear();
            // monkeys[i] = m;
            // itemsProcessed[i] += itemsProcessedByMonkey;
        }
        cout << "Finished round " << j << endl;
    }

    return itemsProcessed;
}

long calculateMonkeyBusiness(vector<Monkey> monkeys) {
    int max1 = 0;
    int max2 = 0;
    for (Monkey m : monkeys) {
        int i = m.itemsProcessed;
        if (i > max1) {
            max2 = max1;
            max1 = i;
        } else if (i > max2) {
            max2 = i;
        }
    }
    return max1 * max2;
}

int main() {
    vector<string> values = getValuesFromFile("test-input.txt");
    vector<Monkey> monkeys = initializeMonkeys(values);
    for (Monkey m : monkeys) {
        for (int item : m.items) {
            cout << item << ", ";
        }
        cout << endl;
    }
    vector<int> itemsProcessed = runSimulation(&monkeys, 10000);
    for (int i : itemsProcessed) {
        cout << i << endl;
    }
    long monkeyBusiness = calculateMonkeyBusiness(monkeys);
    cout << monkeyBusiness << endl;
    // 1515578115 is too low
    // 31422410019 is wrong

    return 0;
}