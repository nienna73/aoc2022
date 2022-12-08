#include "../getValuesFromFile.h"
#include <vector>
#include <string>
#include <iostream>

int stringToInt(char val) {
    if (val == '0') {
        return 0;
    }
    if (val == '1') {
        return 1;
    }
    if (val == '2') {
        return 2;
    }
    if (val == '3') {
        return 3;
    }
    if (val == '4') {
        return 4;
    }
    if (val == '5') {
        return 5;
    }
    if (val == '6') {
        return 6;
    }
    if (val == '7') {
        return 7;
    }
    if (val == '8') {
        return 8;
    }
    if (val == '9') {
        return 9;
    }

    return -1;

}

bool isEdge(vector<string> input, int i, int j) {
    if (i == 0 || i == input.size() - 1) {
        return true;
    }
    if (j == 0 || j == input[0].size() - 1) {
        return true;
    }
    return false;
}

bool visibleToRight(vector<string> input, int i, int j) {
    if (isEdge(input, i, j)) {
        return true;
    }
    int val = stringToInt(input[i][j]);
    j++;
    while(j < input[0].size()) {
        if(stringToInt(input[i][j]) >= val) {
            // cout << "Val " << val << " is smaller than " << input[i][j] << endl;
            return false;
        }
        j++;
    }
    return true;
}

bool visibleToLeft(vector<string> input, int i, int j) {
    if (isEdge(input, i, j)) {
        return true;
    }
    int val = stringToInt(input[i][j]);
    j--;
    while(j >= 0) {
        if(stringToInt(input[i][j]) >= val) {
            return false;
        }
        j--;
    }
    return true;
}

bool visibleToBottom(vector<string> input, int i, int j) {
    if (isEdge(input, i, j)) {
        return true;
    }
    int val = stringToInt(input[i][j]);
    i++;
    while(i < input.size()) {
        if(stringToInt(input[i][j]) >= val) {
            return false;
        }
        i++;
    }
    return true;
}

bool visibleToTop(vector<string> input, int i, int j) {
    if (isEdge(input, i, j)) {
        return true;
    }
    int val = stringToInt(input[i][j]);
    i--;
    while(i >= 0) {
        if(stringToInt(input[i][j]) >= val) {
            return false;
        }
        i--;
    }
    return true;
}

int findVisibleTrees(vector<string> input) {
    int width = input[0].length();
    int height = input.size();
    int canSee = 0;
    vector<vector<bool> > isVisible;

    // initialize that vector
    for (int i = 0; i < height; i++) {
        vector<bool> line;
        for (int j = 0; j < width; j++) {
            line.push_back(false);
        }
        isVisible.push_back(line);
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (visibleToRight(input, i, j)) {
                canSee += 1;
                isVisible[i][j] = true;
            } else if (visibleToLeft(input, i, j)) {
                canSee += 1;
                isVisible[i][j] = true;
            } else if (visibleToBottom(input, i, j)) {
                canSee += 1;
                isVisible[i][j] = true;
            } else if (visibleToTop(input, i, j)) {
                canSee += 1;
                isVisible[i][j] = true;
            }
        }
    }

    return canSee;
}

int scoreToTop(vector<string> input, int k, int j) {
    int val = stringToInt(input[k][j]);
    k--;
    int score = 0;
    for (int i = k; i >= 0; i--) {
        if (stringToInt(input[i][j]) <= val) {
            score++;
        }
        if (stringToInt(input[i][j]) >= val) {
            return score;
        }
    }
    return score;
}

int scoreToRight(vector<string> input, int i, int k) {
    int val = stringToInt(input[i][k]);
    k++;
    int score = 0;
    for (int j = k; j < input[0].size(); j++) {
        if (stringToInt(input[i][j]) <= val) {
            score++;
        }
        if (stringToInt(input[i][j]) >= val) {
            return score;
        }
    }
    return score;
}

int scoreToBottom(vector<string> input, int k, int j) {
    int val = stringToInt(input[k][j]);
    k++;
    int score = 0;
    for (int i = k; i < input.size(); i++) {
        if (stringToInt(input[i][j]) <= val) {
            score++;
        }
        if (stringToInt(input[i][j]) >= val) {
            return score;
        }
    }
    return score;
}

int scoreToLeft(vector<string> input, int i, int k) {
    int val = stringToInt(input[i][k]);
    k--;
    int score = 0;
    for (int j = k; j >= 0; j--) {
        if (stringToInt(input[i][j]) <= val) {
            score++;
        }
        if (stringToInt(input[i][j]) >= val) {
            return score;
        }
    }
    return score;
}

int findScenicScore(vector<string> input, int i, int j) {
    int scoreTop = scoreToTop(input, i, j);
    int scoreRight = scoreToRight(input, i, j);
    int scoreBottom = scoreToBottom(input, i, j);
    int scoreLeft = scoreToLeft(input, i, j);

    long int score = scoreTop * scoreRight * scoreBottom * scoreLeft;
    return score;
}

int findHighestScenicScore(vector<string> input) {
    int height = input.size();
    int width = input[0].size();
    long int maxScore = 0;
    int maxI = 0;
    int maxJ = 0;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            long int score = findScenicScore(input, i, j);
            if (score > maxScore) {
                maxScore = score;
                maxI = i;
                maxJ = j;
            }
        }
    }

    cout << maxI << ", " << maxJ << endl;

    return maxScore;

}

int main() {
    vector<string> input = getValuesFromFile("input.txt");
    int visibleTrees = findVisibleTrees(input);
    cout << "Part one: " << visibleTrees << endl;
    int highestScenicScore = findHighestScenicScore(input);
    cout << "Part two: " << highestScenicScore << endl;

    // test cases
    // vector<string> testInput = getValuesFromFile("test-input.txt");
    // int testVisibleTrees = findVisibleTrees(testInput);
    // cout << "one: " << testVisibleTrees << endl;

    // vector<string> testInput2 = getValuesFromFile("test-input-2.txt");
    // int testVisibleTrees2 = findVisibleTrees(testInput2);
    // cout << "two: " << testVisibleTrees2 << endl;

    // vector<string> testInput3 = getValuesFromFile("test-input-3.txt");
    // int testVisibleTrees3 = findVisibleTrees(testInput3);
    // cout << "three: " << testVisibleTrees3 << endl;

    // vector<string> testInput4 = getValuesFromFile("test-input-4.txt");
    // int testVisibleTrees4 = findVisibleTrees(testInput4);
    // cout << "four: " << testVisibleTrees4 << endl;

    return 0;
}