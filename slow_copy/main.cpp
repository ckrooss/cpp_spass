#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

using namespace std;
using namespace literals::chrono_literals;

namespace {
    struct Slow {
        Slow() {
            cout << "Slow::Slow()" << endl;
            this_thread::sleep_for(100ms);
        }

        Slow(const Slow&) {
            cout << "Slow(const Slow&)" << endl;
            this_thread::sleep_for(100ms);
        }

        Slow(Slow&&) noexcept {
            cout << "Slow(Slow&&)" << endl;
        }

        Slow& operator=(const Slow&) {
            cout << "Slow& operator=(const Slow&)" << endl;
            this_thread::sleep_for(100ms);
            return *this;
        }

        Slow& operator=(Slow&&) noexcept {
            cout << "Slow& operator=(Slow&&)" << endl;
            return *this;
        }
    };
}

int main() {
    cout << "Building vector..." << endl;
    vector<Slow> slows{10};
    cout << "done" << endl;

    cout << "Resizing vector..." << endl;
    slows.resize(10);
    cout << "done" << endl;

    cout << "Removing first..." << endl;
    slows.erase(slows.begin());
    cout << "Done" << endl;

    cout << "Starting for loop..." << endl;
    for (auto& _ : slows) {
        cout << "x";
    }
    cout << "done" << endl;
}
