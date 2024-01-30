#include <iostream>
#include "lib.hpp"

int main() {
    auto d = get_data();
    std::cout << (*d).at(0) << std::endl;
}
