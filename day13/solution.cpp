#include "../getValuesFromFile.h"
#include "../split.h"
#include <vector>
#include <string>
#include <iostream>

vector<string> removeBlankLines(vector<string> input) {
    vector<string> ret;
    for (string s : input) {
        if (s.size()) {
            ret.push_back(s);
        }
    }
    return ret;
}

vector<string> fixValues(vector<string> input) {
    vector<string> ret;
    for (string s : input) {
        string tmp = "";
        for (char c : s) {
            if (isdigit(c)) {
                tmp.append(1,'[');
                tmp.append(1, c);
                tmp.append(1, ']');
            } else {
                tmp += c;
            }
        }
        ret.push_back(tmp);
    }
    return ret;
}

int findEndIndex(string part, int i) {
    int ret = i;
    for (int j = i; j < part.length(); j++) {
        if (part[j] == ']') {
            return j;
        }
    }
    return ret;
}

string getStringChunk(string s, int start, int end) {
    string ret = "";
    for (int i = start; i <= end; i++) {
        ret += s[i];
    }
    return ret;
}

int countChar(string s, char c) {
    int count = 0;
    for (char a : s) {
        if (a == c) {
            count += 1;
        }
    }
    return count;
}

bool containsDigit(string s) {
    for (int i = 0; i < s.length(); i++) {
        if (isdigit(s[i])) {
            return true;
        }
    }
    return false;
}

int getDigit(string c) {
    string ret = "";
    for (int i = 0; i < c.length(); i++) {
        if (isdigit(c[i])) {
            ret += c[i];
        }
    }
    return stoi(ret);
}

string findChunk(string part, int j) {
    int openBracketsNeeded = 0;
    int openBracketsFound = 0;
    int closeBracketsFound = 0;
    string ret = "";
    for (char c : part) {
        if (c == '[' && openBracketsNeeded < j) {
            openBracketsNeeded += 1;
        }
        else if (openBracketsNeeded >= j) {
            if (c == '[') {
                openBracketsFound += 1;
                ret += c;
            } else if (c == ']') {
                closeBracketsFound += 1;
                ret += c;
            } else {
                ret += c;
            } 
            if (openBracketsFound == closeBracketsFound) {
                return ret;
            }
        }
    }
    return ret;
}

int getFirstNumber(string chunk) {
    int ret;
    for (int i = 0; i < chunk.length(); i++) {
        char c = chunk[i];
        if (i+1 < chunk.length()) {
            if (isdigit(c) && isdigit(chunk[i+1])) {
                string number = "";
                number.append(&c);
                number.append(&chunk[i+1]);
                ret = stoi(number);
            }
        } else if (isdigit(c)) {
            ret = (int) c;
        }
    }
    return ret;
}

bool firstNumberBigger(string chunk1, string chunk2) {
    int i1 = getFirstNumber(chunk1);
    int i2 = getFirstNumber(chunk2);
    return i1 > i2;
    
}

vector<tuple<int, bool> > getCorrectPairs(vector<string> input) {
    vector<tuple<int, bool> > ret;
    for (int i = 0; i < input.size(); i += 2) {
        cout << "Pair " << i/2 << endl;
        string part1 = input[i];
        string part2 = input[i+1];
        vector<string> part1Split = splitString(part1, ',');
        vector<string> part2Split = splitString(part2, ',');
        int j = 1;
        int k = 1;
        int numOpen1 = 0;
        int numClose1 = 0;
        int numOpen2 = 0;
        int numClose2 = 0;
        bool insideList;
        tuple<int, bool> pair = make_tuple(-1, false);
        while (j < part1.length() && k < part2.length()) {
            char c1 = part1[j];
            char c2 = part2[k];
            if (j >= part2.length()) {
                // right side ran out of items
                pair = make_tuple(1/2, false);
                j = part1.length();
            }
            else if (isdigit(c1) && isdigit(c2)) {
                if ((int) c1 > (int) c2) {
                    pair = make_tuple(i/2, false);
                    j = part1.length();
                } else if ((int) c1 < (int) c2) {
                    pair = make_tuple(i/2, true);
                    j = part1.length();
                }
            } else if (c1 != ']' && c2 != ']') {
                while (!isdigit(c1)) {
                    c1 = part1[j];
                    j++;
                }
                while (!isdigit(c2)) {
                    c2 = part2[k];
                    k++;
                }
                if ((int) c1 > (int) c2) {
                    pair = make_tuple(i/2, false);
                    j = part1.length();
                } else if ((int) c1 < (int) c2) {
                    pair = make_tuple(i/2, true);
                    j = part1.length();
                }
            } else if (isdigit(c1) && c2 == '[') {
                pair = make_tuple(i/2, true);
                j = part1.length();
            } else {
                if (isdigit(c1) && c2 == ']') {
                    pair = make_tuple(i/2, false);
                    j = part1.length();
                } else if (isdigit(c2) && c1 == ']') {
                    pair = make_tuple(i/2, true);
                    j = part1.length();
                }
            }
            j++;
            k++;
        }
        if (get<0>(pair) == -1) {
            if (part1.size() > part2.size()) {
                pair = make_tuple(i/2, false);
            } else {
                pair = make_tuple(i/2, true);
            }
        }
        cout << get<1>(pair) << endl;
        ret.push_back(pair);
    }
    return ret;
}

int getSumPairsInRightOrder(vector<tuple<int, bool> > pairs) {
    int ret = 0;
    for (tuple<int, bool> t : pairs) {
        if (get<1>(t)) {
            cout << "Index: " << get<0>(t) << endl;
            ret += get<0>(t) + 1;
        }
    }
    return ret;
}

int main() {
    vector<string> values = getValuesFromFile("input.txt");
    values = removeBlankLines(values);
    vector<tuple<int, bool> > correctIndexes = getCorrectPairs(values);
    int sum = getSumPairsInRightOrder(correctIndexes);
    cout << "Sum: " << sum << endl;
    return 0;
    // Part 1:
    // 2856 is too low
    // 5611 is too low
    // 5722 is too low
    // 5810 is wrong
    // 6208 is wrong
    // 6388 is wrong
    // 5892 is wrong
    // 5825 is wrong
}