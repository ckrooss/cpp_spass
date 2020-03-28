#include <iostream>
//#include <unistd.h>
#include <chrono>
#include <thread>
#include <cassert>
#include <random>
#include <vector>
#include <algorithm>

#define NVEC 10000000

using namespace std;
using namespace std::literals::chrono_literals;

void regular_for(uint8_t* data) {
    int cnt{0};
    auto a = chrono::high_resolution_clock::now();
    for (size_t idx = 0; idx < NVEC; idx++) {
        if (data[idx] >= 128)
            cnt++;
    }
    auto b = chrono::high_resolution_clock::now();
    cout << to_string((b - a).count()) << endl;
}

void iterator_for(const vector<uint8_t>& data) {
    int cnt{0};
    auto a = chrono::high_resolution_clock::now();
    for (auto it = data.begin(); it < data.end(); it++) {
        if (*it >= 128)
            cnt++;
    }
    auto b = chrono::high_resolution_clock::now();
    cout << to_string((b - a).count()) << endl;
}

void range_based_for(const vector<uint8_t>& data) {
    int cnt{0};
    auto a = chrono::high_resolution_clock::now();
    for (const auto& d : data) {
        if (d >= 128)
            cnt++;
    }
    auto b = chrono::high_resolution_clock::now();
    cout << to_string((b - a).count()) << endl;
}

int main() {
    random_device rd;  //Will be used to obtain a seed for the random number engine
    mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    uniform_int_distribution<> dis(0, 255);

    vector<uint8_t> data;
    data.resize(NVEC);

    for (auto& d : data) {
        d = static_cast<uint8_t>(dis(gen));
    }
    regular_for(data.data());
    iterator_for(data);
    range_based_for(data);

    cout << "regular" << endl;
    regular_for(data.data());
    regular_for(data.data());
    regular_for(data.data());

    cout << "iterator" << endl;
    iterator_for(data);
    iterator_for(data);
    iterator_for(data);

    cout << "range" << endl;
    range_based_for(data);
    range_based_for(data);
    range_based_for(data);
}
