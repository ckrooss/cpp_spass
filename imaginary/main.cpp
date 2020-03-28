#include <iostream>
#include "complex_numbers.h"

using namespace std;

int main() {
    auto a = 1_r;
    auto b = 1_im;
    auto c = std::move(a + std::move(b));
    cout << a << " + " << b << " = " << c << endl;
}
