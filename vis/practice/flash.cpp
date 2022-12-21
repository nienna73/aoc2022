#include <iostream>
#include <cstring>
#include <unistd.h>

using namespace std;


int main() {
    cout << "hello" << flush;
    sleep(1);
    cout << "\\33[2K\r" << flush;
    return 0;

}