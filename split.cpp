#include <vector>
#include <string>
using namespace std;

vector<string> splitString(string s, char delimiter) {
    vector<string> ret;
    string part = "";
    int length = s.length();

    for (int i = 0; i < length; i++) {
        char c = s[i];
        if (c == delimiter) {
            ret.push_back(part);
            part = "";
        } else {
            part += c;
        }
    }
    ret.push_back(part);

    return ret;
}

vector<char *> splitChar(string val, char delimiter) {
    vector<char* > ret;
    char* part;
    int length = val.length();

    for (int i = 0; i < length; i++) {
        char c = val[i];
        if (c == delimiter) {
            ret.push_back(part);
            part = new char;
        } else {
            part += c;
        }
    }
    ret.push_back(part);

    return ret;
}