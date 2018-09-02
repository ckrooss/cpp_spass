#include <iostream>
#include "complex.h"

using namespace std;

int main(){
    auto a = 1_r;
    auto b = 1_im;
    auto c = std::move(a + std::move(b));
    cout << a << " + " << b << " = " << c << endl;
}
