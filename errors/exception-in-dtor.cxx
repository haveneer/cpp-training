//#region [Collapse all]
#include <iostream>
#include <stdexcept>
#include <string>

void log(const std::string &) {
  std::string log_file{};
  if (log_file.empty())
    throw std::runtime_error("No log file");
}

class X {
public:
  ~X() { log("X::~X"); }
};

int main() {
  try {
    X x;
  } catch (std::exception &e) {
    std::cerr << "Caught exception: " << e.what() << "\n";
  }
}
//#endregion