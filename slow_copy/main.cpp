#include <iostream>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <cassert>
#include <random>
#include <vector>
#include <mutex>
#include <algorithm>

using namespace std;
using namespace literals::chrono_literals;

struct Slow {
    Slow() {
        cout << "Slow::Slow()" << endl;
        this_thread::sleep_for(100ms);
    }

    Slow(const Slow&) {
        cout << "Slow(const Slow&)" << endl;
        this_thread::sleep_for(100ms);
    }

    Slow(Slow&&) {
        cout << "Slow(Slow&&)" << endl;
        this_thread::sleep_for(100ms);
    }

    Slow& operator=(const Slow&) {
        cout << "Slow& operator=(const Slow&)" << endl;
        this_thread::sleep_for(100ms);
        return *this;
    }

    Slow& operator=(Slow&&) {
        cout << "Slow& operator=(Slow&&)" << endl;
        this_thread::sleep_for(100ms);
        return *this;
    }
};

int main() {
    cout << "Building vector..." << endl;
    vector<Slow> slows{0};
    cout << "done" << endl;

    cout << "Resizing vector..." << endl;
    slows.resize(10);
    cout << "done" << endl;

    cout << "Starting for loop..." << endl;
    for (auto& _ : slows) {
        cout << "x";
    }
    cout << "done" << endl;
}
