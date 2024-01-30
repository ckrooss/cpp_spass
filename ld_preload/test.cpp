#include <iostream>
#include <assert.h>
#include "lib.hpp"

int main() {
    auto d = get_data();
    assert((*d).at(0) == "4");
}
