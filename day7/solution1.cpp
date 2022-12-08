#include "../getValuesFromFile.h"
#include "../split.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <stdio.h>

class Directory;
class File;

class Directory{
    public:
        std::string name;
        Directory* parent;
        std::vector<File> children;
        std::vector<Directory*> subDirectories;
        int size;
};

class File{
    public:
        Directory parent;
        std::string name;
        int size;
};

Directory* findDirectory(Directory *home, std::string name) {
    cout << "Name: " << name << endl;
    cout << home->subDirectories.size() << endl;
    for (Directory* subDir : home->subDirectories) {
        cout << "Subdir name: " << subDir->name << endl;
        if (subDir->name == "$") {
            cout << "wtf" << endl;
            continue;
        }
        if (subDir->name == name) {
            return subDir;
        }
    }
    cout << endl;
    cout << "Did not find directory " << name << " in folder " << home->name << endl;
}


void pushDirectoriesToDir(Directory* active, std::vector<Directory> dirs) {
    for (Directory &d : dirs) {
        cout << "Added " << d.name << " to parent directory " << active->name << endl;
        d.parent = active;
    }

}

bool listContains(std::vector<char*> l, char* s) {
    // check if l contains s
    for (char* k : l) {
        cout << s << " " << k << endl;
        if (strcmp(k, s) == 0) {
            return true;
        }
    }

    return false;

}

Directory* getDirectory(Directory current, string name) {
    cout << "called getDirectory for " << name << endl;
    int length = current.subDirectories.size();
    for (int i = 0; i < length; i++) {
        Directory* subdir = current.subDirectories[i];
        cout << subdir->name << endl;
        if (subdir->name == name) {
            return subdir;
        }
    }
}

void addDirectories(Directory* current, std::vector<Directory> directories) {
    for (Directory dir : directories) {
        cout << "Add " << dir.name << " to " << current->name << endl;
        current->subDirectories.push_back(&dir);
    }
}

void addFiles(Directory* current, std::vector<File> files) {
    for (File f : files) {
        current->children.push_back(f);
    }
}

Directory initializeFileStructure(std::vector<std::string> input) {
    Directory home;
    home.name = "home";
    home.parent = NULL;
    Directory* current;
    std::vector<Directory> allDirectories;
    std::vector<File> allFiles;
    for (std::string &line : input) {
        // declaring character array
        char* lineChar;
 
        // copying the contents of the
        // string to char array
        strcpy(lineChar, line.c_str());
        std::vector<char*> splitline = splitChar(line, ' ');
        cout << "HERE: " << lineChar << " " << strcmp(lineChar, "$") << endl;
        if (strcmp(lineChar, "$") == 32) {
            cout << "111" << endl;
            addDirectories(current, allDirectories);
            addFiles(current, allFiles);
            allDirectories.clear();
            allFiles.clear();
        }

        if (strcmp(lineChar, "..") == 32) {
            cout << "119" << endl;
            // change directory up
            cout << current->name << endl;
            current = current->parent;
            cout << current->name << endl;
        } 
        if (strcmp(lineChar, "/") == 32) {
            cout << "126" << endl;
            // change directory home
            cout << "/ matched line " << line << endl;
            current = &home;
        } 
        else if (strcmp(lineChar, "cd") == 32) {
            cout << "132" << endl;
            // change directory to name
            char* name = splitline[2];
            current = getDirectory(*current, name);
            cout << "Changed to directory " << current->name << endl;
        } 
        else if (strcmp(lineChar, "dir") == 32) {
            cout << "139" << endl;
            // add directory
            char* dirname = splitline[1];
            Directory newdir;
            newdir.name = dirname;
            newdir.parent = current;
            allDirectories.push_back(newdir);
        } 
        else if (!(strcmp(lineChar,  "$") == 32)) {
            cout << "148" << endl;
            // add file
            char* filename = splitline[1];
            int size = atoi(splitline[0]);
            File newfile;
            newfile.name = filename;
            newfile.parent = *current;
            newfile.size = size;
            current->size += size;
            allFiles.push_back(newfile);
        }
    }

    return home;
}

int main() {

    std::vector<std::string> input = getValuesFromFile("input.txt");
    Directory fileStructure = initializeFileStructure(input);
    cout << fileStructure.subDirectories.size() << endl;

    return 0;
}