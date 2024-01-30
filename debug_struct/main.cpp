#include <vector>
#include <stdint.h>
#include <iostream>

using std::cout;
using std::endl;

typedef struct {
    char b[5];
} c_t;

int main() {
    c_t o;

    for (int idx = 0; idx <= 4; idx++) {
        cout << std::to_string(o.b[idx]) << endl;
    }
}
