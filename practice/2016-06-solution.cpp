#include "../getValuesFromFile.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

#define IS_TRUE(x) { if (!x) cout << __FUNCTION__ << " failed at line " << __LINE__ << endl; }

vector<string> rowsToColumns(vector<string> rows) {
    int width = rows.size();
    int height = rows[0].size();

    vector<string> columns;
    for (int i = 0; i < height; i++) {
        string column = "";
        for (int j = 0; j < width; j++) {
            column += rows[j][i];
        }
        columns.push_back(column);
    }

    return columns;
}

char findLeastCommon(string s) {
    map<char, int> counts;

    int length = s.length();

    for (int i = 0; i < length; i++) {
        char c = s[i];
        if (counts.find(c) == counts.end()) {
            counts[c] = 1;
        } else {
            counts[c] += 1;
        }
    }

    map<char, int>::iterator it = counts.begin();
    int smallestCount = 550;
    char ret = '0';
    while (it != counts.end()) {
        int count = it->second;
        char c = it->first;

        if (count < smallestCount) {
            smallestCount = count;
            ret = c;
        }

        it++;
    }

    return ret;
}

string decodeMessage(vector<string> message) {
    string secretMessage = "";

    vector<string> columns = rowsToColumns(message);

    int length = columns.size();

    for (int i = 0; i < length; i++) {
        // part 1
        // char mostCommonLetter = findMostCommon(columns[i]);
        // part 2
        char leastCommonLetter = findLeastCommon(columns[i]);
        secretMessage += leastCommonLetter;
    }

    return secretMessage;
}

// tests

void test_decodeMessage() {
    vector<string> input = getValuesFromFile("2016-06-test-input.txt");
    IS_TRUE((decodeMessage(input) == "advent"));
}

void test_rowsToColumns() {
    vector<string> input;
    input.push_back("abc");
    input.push_back("abc");
    input.push_back("abc");
    input.push_back("abc");
    input.push_back("abc");

    vector<string> expected;
    expected.push_back("aaaaa");
    expected.push_back("bbbbb");
    expected.push_back("ccccc");

    IS_TRUE((rowsToColumns(input) == expected));
}

int main() {
    test_decodeMessage();
    test_rowsToColumns();

    vector<string> input = getValuesFromFile("2016-06-input.txt");
    string secretMessage = decodeMessage(input);
    cout << secretMessage << endl;

    return 0;
}