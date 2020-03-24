//#region [Declarations]
#include <iostream>
#include <limits>
#include <random>

static struct {
  std::random_device random_device;
  std::default_random_engine eng{random_device()};
  std::uniform_int_distribution<> dist{0, 1};
  bool operator()() { return dist(eng); }
} random_boolean;

const double NaN = std::numeric_limits<double>::quiet_NaN(); // NaN ready to be used
//#endregion

int seed = 1; // [coliru] change me to generate another random number sequence

int main() {
  if (true)
    std::cout << "condition is true\n";

  if (2 != 0) { // same with block declaration
    std::cout << "condition is true\n";
  }

  if (2.1) { // non zero value is used as 'true'
    std::cout << "condition is true\n";
  } else {
    std::cout << "condition is false\n";
  }

  if (random_boolean())
    int x = 2; // local scope variable
  else {
    double x = 3.14; // this is another local variable
  }
  // x no more exists here
  // x; // error: use of undeclared identifier 'x'
}