#include "../getValuesFromFile.h"
#include "../split.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class File;
class Directory;

class File{
    public:
        string name;
        long int size;
        Directory* parent;
};

class Directory{
    public:
        string name;
        vector<File> children;
        vector<Directory*> subDirectories;
        Directory* parent;
};


Directory* findSubDir(Directory* home, string name) {
    for (Directory* d : home->subDirectories) {
        cout << "subdir name: " << d->name << endl;
        if (d->name == name) {
            return d;
        }
    }
}


int main() {
    vector<string> values = getValuesFromFile("input.txt");
    vector<Directory> directories;
    long int doesNotExist = string::npos;
    Directory home;
    home.name = "home";
    Directory* current = &home;

    for (string v : values) {
        if (v.find("dir") != doesNotExist) {
            vector<string> parts = split(v, ' ');
            string name = parts[1];
            Directory d;
            d.name = name;
            directories.push_back(d);
        } 
        else if (v.find("$") != doesNotExist) {
            // this is a command
            int length = directories.size();
            for (int i = 0; i < length; i++) {
                cout << directories[i].name << endl;
                Directory dir = directories[i];
                cout << "Adding " << dir.name << " to " << current->name << endl;
                dir.parent = current;
                current->subDirectories.push_back(&dir);
            }
            directories.clear();

            if (v.find("..") != doesNotExist) {
                current = current->parent;
            } else if (v.find("/") != doesNotExist) {
                current = &home;
            } else if (v.find("cd") != doesNotExist) {
                cout << v << endl;
                vector<string> parts = split(v, ' ');
                string dirname = parts[2];
                cout << dirname << endl;
                if (dirname != ".." && dirname != "/") {
                    cout << current->subDirectories.size() << endl;
                    current = findSubDir(current, dirname);
                }
            }
        }
    }

    return 0;
}