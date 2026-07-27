#include <iostream>
#include "complex_numbers.h"

using namespace std;

int main() {
const     auto a = 4_r + 3_im;
const     auto b = 2_r + 1_im;
const     auto c = a + b;
    cout << a << " + " << b << " = " << c << endl;
    cout << a << " * " << b << " = " << a*b << std::endl;
}
