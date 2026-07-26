#include "nlohmann/json.hpp"
#include <fstream>
#include <iostream>

int main() {
  using json = nlohmann::json;

  json j;
  j["a"] = u8"x\nq";
  j["b"] = u8"y\u0004w";
  j["c"] = u8"z\u000Ae";

  for (const auto &[key, value] : j.items()) {
    std::cout << key << " = " << value << std::endl;
  }

  std::cout << j.dump(4) << std::endl;

  std::ifstream ifs("./testfile");

  auto cb = []([[maybe_unused]] int depth,
               [[maybe_unused]] json::parse_event_t event,
               [[maybe_unused]] json &c) -> bool { std::cout << c.dump() << std::endl;return true; };

  json j2 = json::parse(ifs, cb, false);
  if (j2.is_discarded()) {
    std::cout << "failed to parse json" << std::endl;
  }
}
