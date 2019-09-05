#include <iostream>
using namespace std;

extern "C" void module() {
    cout << "Hello from modB" << endl;
}

