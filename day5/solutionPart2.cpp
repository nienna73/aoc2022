#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <fstream>
using namespace std;

vector<string> split(string line, char delim) {
    vector<string> ret;
    string part;
    for (char &c : line) {
        if (c == delim) {
            ret.push_back(part);
            part = "";
        } else {
            part += c;
        }
    }

    ret.push_back(part);

    return ret;
}

string removeBrackets(string val) {
    string ret = "";
    for (char &c : val) {
        if (c != '[' && c != ']') {
            ret += c;
        }
    }
    return ret;
}

string keepEveryFourthSpace(string val) {
    int skipped = 0;
    string ret = "";
    for (char &c : val) {
        if (skipped %4 == 0 || c != ' ') {
            ret += c;
        }
        skipped += 1;
    }
    return ret;
}

vector<char> valToRow(string val) {
    vector<char> row;
    val = removeBrackets(val);
    val = keepEveryFourthSpace(val);
    for (char &c : val) {
        row.push_back(c);
    }
    return row;
}

deque<vector<char> > addBuffers(deque<vector<char> > v, int buffer, int length) {
    for (int i = 0; i < buffer; i++) {
        vector<char> row;
        for (int j = 0; j < length; j++) {
            row.push_back(' ');
        }
        v.push_front(row);
    }
    return v;
}

vector<string> removeWords(vector<string> moves) {
    vector<string> ret;
    long int doesNotExist = string::npos;
    string words = "move from to";      // these are the only words used
    for (string &line : moves) {
        string justTheNumbers = "";
        vector<string> splitLine = split(line, ' ');
        for (string &part : splitLine) {
            if (words.find(part) == doesNotExist) {
                justTheNumbers += part + " ";
            }
        }
        ret.push_back(justTheNumbers);
    }
    return ret;
}

vector<vector<char> > dequeToVector(deque<vector<char> > cargo) {
    vector<vector<char> > ret;
    for(vector<char> &line : cargo) {
        ret.push_back(line);
    }
    return ret;
}

void printTopElement(vector<vector<char> > cargo) {
    int height = cargo.size();
    int width = cargo[0].size();
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (cargo[j][i] != ' ') {
                cout << cargo[j][i];
                break;
            }
        }
    }
    cout << endl;
}

// referencing: https://stackoverflow.com/questions/52273110/how-do-i-write-a-unit-test-in-c
// If parameter is not true, test fails
// This check function would be provided by the test framework
#define IS_TRUE(x) { if (!(x)) std::cout << __FUNCTION__ << " failed on line " << __LINE__ << std::endl; }

void test_removeWords() {
    // case 1
    vector<string> input;
    input.push_back("move 6 from 1 to 7");
    vector<string> output;
    output.push_back("6 1 7 ");
    IS_TRUE((removeWords(input) == output));

    // case 2
    input.clear();
    input.push_back("move 13 from 4 to 2");
    output.clear();
    output.push_back("13 4 2 ");

    IS_TRUE((removeWords(input) == output));
}

int main() {
    test_removeWords();
    fstream input;
    input.open("input.txt");

    deque<vector<char> > cargo;
    vector<string> moves;
    long int doesNotExist = string::npos;
    int length = 0;

    if (input.is_open()) {
        string val;
        while (getline(input, val)) {
            if (val.find("move") != doesNotExist) {
                moves.push_back(val);
            } else if (val.find('[') != doesNotExist) {
                cout << val << endl;
                vector<char> row = valToRow(val);
                cargo.push_back(row);
                if (length == 0) {
                    length = row.size();
                }
            }
        }
    }

    input.close();

    // I don't know how tall my cargo can get,
    // so I'm going to add 20 buffer rows to the top
    cargo = addBuffers(cargo, 50, length);
    moves = removeWords(moves);
    vector<vector<char> > fixedCargo = dequeToVector(cargo);
    int height = fixedCargo.size();
    int width = fixedCargo[0].size();
    
    for (string &s : moves) {
        // move s[0] crates
        // from s[1] column
        // to s[2] column
        vector<string> parts = split(s, ' ');
        
        int numCrates = stoi(parts[0]);
        int startColumn = stoi(parts[1]);
        int endColumn = stoi(parts[2]);
        startColumn = startColumn - 1;  // we zero index here
        endColumn = endColumn - 1;
        vector<char> toMove; // contains all letters to move in the order they were found
        for (int i = 0; i < numCrates; i++) {
            for (int j = 0; j < height; j++) {
                if (fixedCargo[j][startColumn] != ' ') {
                    // we've found a letter to move
                    char letter = fixedCargo[j][startColumn];
                    toMove.push_back(letter);
                    fixedCargo[j][startColumn] = ' ';      // clear the crate
                    break;
                }
            }
        }
        bool added = false;
        for (int k = toMove.size() - 1; k >= 0; k--) {
            for (int j = 0; j < height; j++) {
                if (fixedCargo[j][endColumn] != ' ') {
                    // go one above the first non-empty space
                    if (j-1 >= 0) {
                        fixedCargo[j-1][endColumn] = toMove[k];
                        added = true;
                        break;
                    }
                }
            }
            if (!added) {
                // the column is empty
                fixedCargo[height-1][endColumn] = toMove[k];
            }
            added = false;
        }
    }

    printTopElement(fixedCargo);

    return 0;

}
