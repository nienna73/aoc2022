#include "../getValuesFromFile.h"
#include "../split.h"
#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <deque>

class Monkey{
    public:
        vector<long long> items;
        long long itemsInspected;
        char operation;
        long long factor;
        long long test;
        long long ifTrue;
        long long ifFalse;

        void operator=(Monkey *rhs) {
            items = rhs->items;
            itemsInspected = rhs->itemsInspected;
            operation = rhs->operation;
            factor = rhs->factor;
            test = rhs->test;
            ifTrue = rhs->ifTrue;
            ifFalse = rhs->ifFalse;
        }

        void print() {
            cout << items.size() << endl;
            cout << itemsInspected << endl;
            cout << operation << " " << factor << endl;
            cout << test << endl;
            cout << ifTrue << endl;
            cout << ifFalse << endl;
        }
};

char getOperation(string s) {
    // input example: Operation: new = old * 19
    // return from that input: *
    long doesNotExist = string::npos;
    if (s.find('*') != doesNotExist) {
        return 'm';
    } else if (s.find('+') != doesNotExist) {
        return 'a';
    }

    cout << "Could not find correct operation, returning add" << endl;
    return 'a';
}

// referencing: https://www.delftstack.com/howto/cpp/how-to-determine-if-a-string-is-number-cpp/
bool isNumber(const string& str)
{
    return str.find_first_not_of("0123456789") == string::npos;
}

long long getLast(string s) {
    // input example: Operation: new = old * 19
    // return from that input: 19
    vector<string> parts = splitString(s, ' ');
    if (isNumber(parts[parts.size() - 1])) {
        long long ret = stol(parts[parts.size() - 1]);
        return ret;
    } if (parts[parts.size() - 1] == "old") {
        return -1;
    }
    cout << "Something went wrong converting " << parts[parts.size() - 1] << " to a digit" << endl;
    int ret = 0;
    return ret;
}

vector<Monkey> initializeMonkeys(vector<string> input) {
    Monkey m;
    vector<Monkey> ret;
    long doesNotExist = string::npos;
    for (string &s : input) {
        if (s.find("Monkey") != doesNotExist) {
            m = new Monkey;
            m.itemsInspected = 0;
        } else if (s.find("items") != doesNotExist) {
            vector<string> parts = splitString(s, ':');
            vector<string> items = splitString(parts[1], ',');
            for (string &item : items) {
                m.items.push_back(stol(item));
            }
        } else if (s.find("Operation:") != doesNotExist) {
            m.operation = getOperation(s);
            m.factor = getLast(s);
        } else if (s.find("Test:") != doesNotExist) {
            m.test = getLast(s);
        } else if (s.find("true") != doesNotExist) {
            m.ifTrue = getLast(s);
        } else if (s.find("false") != doesNotExist) {
            m.ifFalse = getLast(s);
        } else if (s.size() == 0) {
            ret.push_back(m);
        }
    }
    ret.push_back(m);

    return ret;
}

vector<unsigned long long> runSimulation(vector<string> input, vector<Monkey> *monkeys, long rounds, int worryLevel) {
    long i = 1;
    vector<unsigned long long> counts;
    for (int k = 0; k < monkeys->size(); k++) {
        counts.push_back(0);
    }
    int shared_modulus = 1;
    for (int i = 0; i < monkeys->size(); i++) {
        shared_modulus *= monkeys->at(i).test;
    }
    while (i <= rounds) {
        int j = 0;
        for (Monkey &activeMonkey : *monkeys) {
            cout << "Processing monkey " << j << endl;
            for (unsigned long long item : activeMonkey.items) {
                counts[j] += 1;
                int factor = activeMonkey.factor;
                activeMonkey.itemsInspected += 1;
                if (factor == -1) {
                    factor = item;
                    cout << "set factor to item" << endl;
                }
                if (activeMonkey.operation == 'm') {
                    item = item * factor;
                } else if (activeMonkey.operation == 'a') {
                    item = item + factor;
                }
                // item = floor(item / worryLevel);
                item = item % shared_modulus;
                if ((item % activeMonkey.test) == 0) {
                    cout << "moving " << item << " from " << j << " to " << activeMonkey.ifTrue << endl;
                    monkeys->at(activeMonkey.ifTrue).items.push_back(item);
                } else {
                    cout << "moving " << item << " from " << j << " to " << activeMonkey.ifFalse << endl;
                    monkeys->at(activeMonkey.ifFalse).items.push_back(item);
                }
            }
            j++;
            activeMonkey.items.clear();
        }
        cout << "Finished round " << i << endl;
        i++;
    }
    return counts;
}

unsigned long long findMonkeyBusiness(vector<Monkey> monkeys) {
    long firstHighest = 0;
    long secondHighest = 0;

    for (Monkey m : monkeys) {
        cout << m.itemsInspected << endl;
        if(m.itemsInspected > firstHighest) {
            secondHighest = firstHighest;
            firstHighest = m.itemsInspected;
        } else if (m.itemsInspected > secondHighest) {
            secondHighest = m.itemsInspected;
        }
    }

    return firstHighest * secondHighest;

}

unsigned long long findBusiness(vector<unsigned long long> counts) {
    long long firstHighest = 0;
    long long secondHighest = 0;
    for (long long c : counts) {
        cout << c << endl;
        if (c > firstHighest) {
            secondHighest = firstHighest;
            firstHighest = c;
        } else if (c > secondHighest) {
            secondHighest = c;
        }
    }

    unsigned long long ret = firstHighest * secondHighest;

    return ret;

}

#define IS_TRUE(x) { if (!x) cout << __FUNCTION__ << " failed at line " << __LINE__ << endl; }

void test_getLast() {
    string input = "Operation: new = old * 19";
    int output = 19;
    IS_TRUE((getLast(input) == output));

    input = "Test: divisible by 3";
    output = 3;
    IS_TRUE((getLast(input) == output));

    input = "If true: throw to monkey 2";
    output = 2;
    IS_TRUE((getLast(input) == output));

    input = "Operation: new = old * old";
    output = -1;
    IS_TRUE((getLast(input) == output));
}

int main() {
    test_getLast();
    vector<string> input = getValuesFromFile("input.txt");
    vector<Monkey> monkeys = initializeMonkeys(input);


    cout << "Running simulation..." << endl;
    vector<unsigned long long> counts = runSimulation(input, &monkeys, 10000, 1);
    unsigned long long monkeyBusiness = findMonkeyBusiness(monkeys);
    // unsigned long long monkeyBusiness = findBusiness(counts);
    cout << "Monkey business: " << monkeyBusiness << endl;      
    
    // Part 1: 182293
    // Part 2:
    // 46423787776 is too low
    // 46224695250 is wrong
    // 153947
    // 157300
    // 31422410019 is too low

    return 0;
}