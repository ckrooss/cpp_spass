#include "nlohmann/json.hpp"
#include <iostream>

int main() {
    using json = nlohmann::json;

    json j;
    j["a"] = u8"x\nq";
    j["b"] = u8"y\u0004w";
    j["c"] = u8"z\u000Ae";

    for (const auto& [key, value] : j.items()) {
        std::cout << key << " = " << value << std::endl;
    }

    std::cout << j.dump(4) << std::endl;
}
