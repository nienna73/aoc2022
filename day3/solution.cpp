#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;


string firstHalf(string rucksack, int half) {
    string ret = "";
    for (int i = 0; i < half; i++) {
        ret = ret + rucksack[i];
    }

    return ret;
}

string secondHalf(string rucksack, int half) {
    string ret = "";
    for (int i = half; i < rucksack.length(); i++) {
        ret = ret + rucksack[i];
    }

    return ret;
}

char findOverlap(string first, string second) {
    long int doesNotExist = string::npos;
    for (int i = 0; i < first.length(); i++) {
        char character = first[i];
        if (second.find(character) != doesNotExist) {
            return character;
        }
    }

    return '1';
}

char findOverlapOfThree(string first, string second, string third) {
    long int doesNotExist = string::npos;
    for (int i = 0; i < first.size(); i++) {
        char character = first[i];
        if (second.find(character) != doesNotExist && third.find(character) != doesNotExist) {
            return character;
        }
    }

    return '1';
}

vector<vector<string> > chunkValues(vector<string> values) {
    // Breaks the vector down into chunks of 3
    vector<string> temp;
    vector<vector<string> > ret;
    for(int i = 0; i <= values.size(); i++) {
        if (temp.size() == 3) {
            ret.push_back(temp);
            temp.clear();
        }
        temp.push_back(values[i]);
    }
    return ret;
}

int main() {
    fstream input;
    input.open("input.txt");

    vector<string> myValues;

    if (input.is_open()) {
        string val;
        while (getline(input, val)) {
            myValues.push_back(val);
        }
    }

    input.close();

    vector<vector<string> > chunkedValues = chunkValues(myValues);

    int sum = 0;
    string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (vector<string> chunk : chunkedValues) {
        // For the first problem
        // for loop condition: &rucksack : myValues
        // int length = rucksack.length();
        // int half = length / 2;
        // string firstCompartment = firstHalf(rucksack, half);
        // string secondCompartment = secondHalf(rucksack, half);
        // char overlap = findOverlap(firstCompartment, secondCompartment);
        // For the second problem
        string first = chunk[0];
        string second = chunk[1];
        string third = chunk[2];
        char overlap = findOverlapOfThree(first, second, third);
        int pos = alphabet.find(overlap);
        sum += pos + 1;
    }

    cout << sum << endl;
    return sum;
}