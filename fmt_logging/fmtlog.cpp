#include "fmtlog.h"
#include <iostream>

namespace fmtlog {
void output(std::string_view message) {
  std::cout << message << std::endl;
}
}