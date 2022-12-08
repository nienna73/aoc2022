#include "../getValuesFromFile.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

bool hasDuplicates(string s) {
    int length = s.length();
    string seen = "";
    long int doesNotExist = string::npos;

    for (int i = 0; i < length; i++) {
        if (seen.find(s[i]) != doesNotExist) {
            return true;
        } else {
            seen += s[i];
        }
    }

    return false;
}

int findStartOfMessage(string input) {
    int length = input.length();
    // part 1
    // int startOfPacket = 4;
    // part 2
    int startOfMessage = 14;

    for (int i = 0; i < length; i++) {
        string subset = input.substr(i, startOfMessage);
        if (!hasDuplicates(subset)) {
            return i + startOfMessage;
        }
    }

    return -1;
}

// referencing: https://stackoverflow.com/questions/52273110/how-do-i-write-a-unit-test-in-c
// If parameter is not true, test fails
// This check function would be provided by the test framework
#define IS_TRUE(x) { if (!(x)) std::cout << __FUNCTION__ << " failed on line " << __LINE__ << std::endl; }

void test_findStartOfMessage() {
    vector<string> testStrings;
    testStrings.push_back("mjqjpqmgbljsphdztnvjfqwrcgsmlb");
    testStrings.push_back("bvwbjplbgvbhsrlpgdmjqwftvncz");
    testStrings.push_back("nppdvjthqldpwncqszvftbrmjlhg");
    testStrings.push_back("nznrnfrfntjfmvfwmzdfjlvtqnbhcprsg");
    testStrings.push_back("zcfzfwzzqfrljwzlrfnpqdbhtmscgvjw");

    vector<int> answers;
    answers.push_back(19);
    answers.push_back(23);
    answers.push_back(23);
    answers.push_back(29);
    answers.push_back(26);

    int length = testStrings.size();

    for (int i = 0; i < length; i++) {
        IS_TRUE(findStartOfMessage(testStrings[i]) == answers[i]);
    }
}

int main() {
    test_findStartOfMessage();
    vector<string> buffer = getValuesFromFile("input.txt");
    string input = buffer[0];
    int pos = findStartOfMessage(input);
    cout << pos << endl;

    return 0;
}